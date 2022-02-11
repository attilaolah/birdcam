# Nikon Coolpix A900

Build `scan.go` to scan for and connect to Nikon Coolpix A900 devices via
Bluetooth LE.

```sh
$ go build scan.go
$ sudo setcap 'cap_net_raw,cap_net_admin=eip' scan
$ ./scan
```

## De-Obfuscating SnapBridge

To get started, let's download the SnapBridge APK
(`com.nikon.snapbridge.cmru`), e.g. from
[APKPure](https://m.apkpure.com/snapbridge/com.nikon.snapbridge.cmru).
I grabbed version `2.8.3`, and de-obfuscated it with
[JADX](https://github.com/skylot/jadx) like so:

```sh
$ jadx --deobf SnapBridge_v2.8.3.apk
```

There are several files of interest in there. First let's get the ones that
assign the UUIDs to named constants, which helps us understand what the
characteristics are for.

Generic UUIDs are in
`com/nikon/snapbridge/cmru/bleclient/services/device/BleDeviceInformationService.java`:

| Constant                   | UUID                                   |
|----------------------------|----------------------------------------|
| `DEVICE_INFO_UUID`         | `0000180A-0000-1000-8000-00805F9B34FB` |
| `FIRMWARE_REVISION_STRING` | `00002A26-0000-1000-8000-00805F9B34FB` |
| `HARDWARE_REVISION_STRING` | `00002A27-0000-1000-8000-00805F9B34FB` |
| `IEEE_1107320601`          | `00002A2A-0000-1000-8000-00805F9B34FB` |
| `MANUFACTURE_NAME_STRING`  | `00002A29-0000-1000-8000-00805F9B34FB` |
| `MODEL_NUMBER_STRING`      | `00002A24-0000-1000-8000-00805F9B34FB` |
| `PNP_ID`                   | `00002A50-0000-1000-8000-00805F9B34FB` |
| `SERIAL_NUMBER_STRING`     | `00002A25-0000-1000-8000-00805F9B34FB` |
| `SOFTWARE_REVISION_STRING` | `00002A28-0000-1000-8000-00805F9B34FB` |
| `SYSTEM_ID`                | `00002A23-0000-1000-8000-00805F9B34FB` |


NIKON Vendor-specific UUIDs are in
`com/nikon/snapbridge/cmru/bleclient/services/lss/BleLssService.java`:

| Constant                        | UUID                                   |
|---------------------------------|----------------------------------------|
| `AUTHENTICATION`                | `00002000-3DD4-4255-8D62-6DC7B9BD5561` |
| `BATTERY_LEVEL`                 | `00002A19-3DD4-4255-8D62-6DC7B9BD5561` |
| `CLIENT_DEVICE_NAME`            | `00002002-3DD4-4255-8D62-6DC7B9BD5561` |
| `CONNECTION_CONFIGURATION`      | `00002004-3DD4-4255-8D62-6DC7B9BD5561` |
| `CONNECTION_ESTABLISHMENT`      | `00002005-3DD4-4255-8D62-6DC7B9BD5561` |
| `CURRENT_TIME`                  | `00002006-3DD4-4255-8D62-6DC7B9BD5561` |
| `DESCRIPTOR`                    | `00002902-0000-1000-8000-00805F9B34FB` |
| `LOCATION_INFORMATION`          | `00002007-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_CABLE_ATTACHMENT`          | `0000200A-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_CATEGORY_INFO`             | `00002080-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_CONTROL_POINT`             | `00002008-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_CONTROL_POINT_FOR_CONTROL` | `00002021-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_FEATURE`                   | `00002009-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_SERIAL_NUMBER_STRING`      | `0000200B-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_STATUS_FOR_CAPTURE`        | `00002081-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_STATUS_FOR_CONTROL`        | `00002020-3DD4-4255-8D62-6DC7B9BD5561` |
| `LSS_UUID`                      | `0000DE00-3DD4-4255-8D62-6DC7B9BD5561` |
| `POWER_CONTROL`                 | `00002001-3DD4-4255-8D62-6DC7B9BD5561` |
| `SERVER_DEVICE_NAME`            | `00002003-3DD4-4255-8D62-6DC7B9BD5561` |

The obvious candidate here is the `CONNECTION_ESTABLISHMENT` UUID, which
denotes a characteristic used by the phone to enable WiFi on the camera. This
can be confirmed by sniffing the BLE packets between the app an the camera.

To do that, enable developer options on the Android phone, then enable
Bluetooth HCI snoop logging in Settings, or via ADB:

```sh
$ adb shell settings put secure bluetooth_hci_log 1
```

Connect to the camera, enable the WiFi (e.g. by turning on remote photography)
and then generate a bug report using ADB. The bug report is essentially a ZIP
file that contains, among others, the Bluetooth logs in
`FS/data/misc/bluetooth/logs/btsnoop_hci.log`.

This file can be inspected in Wireshark, which reveals that indeed the phone
writes `0x01` to the `CONNECTION_ESTABLISHMENT` characteristic to enable the
WiFi on the camera.

However, trying to do that without authenticating first will cause the camera
to immediately disconnect. So first thing to do is authenticate, using the
`AUTHENTICATION` characteristic.

The characteristic has a descriptor which is used first to subscribe to
indication. The APK does the same in (the now de-obfuscated)
`sources/com/nikon/snapbridge/cmru/bleclient/BleConnection.java`:

```java
public /* synthetic */ void m11905a() {
	// Set Notification for LSS_CONTROL_POINT:
	C5323b.m11956a(BleConnection.f15079a, "set notification");
	// […] return on error

	// Set Indication for AUTHENTICATION:
	C5323b.m11956a(BleConnection.f15079a, "set indication");
	// […] return on error

	C5323b.m11956a(BleConnection.f15079a, "Authentication start");
	// […]
	if (a != BleErrorCodes.OK) {
		C5323b.m11956a(BleConnection.f15079a, "Authentication error");
		// […]
	}
	C5323b.m11956a(BleConnection.f15079a, "Authentication end");
	// […]
}
```

The actual authentication logic is implemented in the `lssAuthProc` method:

```java
@Override // com.nikon.snapbridge.cmru.bleclient.characteristics.lss.IBleAuthentication
public boolean lssAuthProc(byte[] bArr) {
	String str;
	String str2;
	C5323b.m11956a(f15243a, "start lss authentication");
	this.f15246d.init((int) System.currentTimeMillis());
	C5323b.m11956a(f15243a, "start Stage1");
	if (!m11997b(bArr)) {
		str = f15243a;
		str2 = "failure of the authentication process of Stage1";
	} else {
		C5323b.m11956a(f15243a, "start Stage2");
		BleAuthenticationData c = m11998c();
		if (c == null) {
			str = f15243a;
			str2 = "failure of the authentication process of Stage2";
		} else {
			C5323b.m11956a(f15243a, "start Stage3");
			if (!m11996a(c)) {
				str = f15243a;
				str2 = "failure of the authentication process of Stage3";
			} else {
				C5323b.m11956a(f15243a, "start Stage4");
				BleAuthenticationData c2 = m11998c();
				if (c2 == null) {
					str = f15243a;
					str2 = "failure of the authentication process of Stage4";
				} else if (this.f15246d.generateKey(c2.getDeviceId(), bArr) != 0) {
					accessor.mo15432a(BleErrorCodes.ERROR);
					str = f15243a;
					str2 = "generateKey error";
				} else {
					this.f15247e.save(this.f15246d);
					return true;
				}
			}
		}
	}
	C5323b.m11959b(str, str2);
	return false;
}

/* renamed from: a */
private boolean m11996a(BleAuthenticationData bleAuthenticationData) {
	C5326a accessor = getAccessor();
	if (this.f15245c == null) {
		accessor.mo15432a(BleErrorCodes.ERROR);
		return false;
	}
	byte[] stage3 = this.f15246d.stage3(bleAuthenticationData.getNonce(), this.f15245c, bleAuthenticationData.getDeviceId());
	BleAuthenticationData bleAuthenticationData2 = new BleAuthenticationData();
	bleAuthenticationData2.setStage((byte) 3);
	bleAuthenticationData2.setNonce(this.f15245c);
	bleAuthenticationData2.setDeviceId(stage3);
	C5322a.m11949a(f15243a, "writeStage3", bleAuthenticationData2);
	byte[] a = C5365a.m12025a(bleAuthenticationData2);
	return a != null && accessor.mo15434a(this, a);
}

/* renamed from: b */
private boolean m11997b(byte[] bArr) {
	C5326a accessor = getAccessor();
	byte[] stage1 = this.f15246d.stage1();
	if (stage1 == null) {
		accessor.mo15432a(BleErrorCodes.ERROR);
		return false;
	}
	this.f15245c = stage1;
	BleAuthenticationData bleAuthenticationData = new BleAuthenticationData();
	bleAuthenticationData.setStage((byte) 1);
	bleAuthenticationData.setNonce(stage1);
	bleAuthenticationData.setDeviceId(bArr);
	C5322a.m11949a(f15243a, "writeStage1", bleAuthenticationData);
	byte[] a = C5365a.m12025a(bleAuthenticationData);
	return a != null && accessor.mo15434a(this, a);
}
```

The encoding and decoding of authentication data is done in a different class,
`com/nikon/snapbridge/cmru/bleclient/characteristics/lss/datas/p310a/C5365a.java`:

```java
/* renamed from: a */
public static BleAuthenticationData m12024a(byte[] bArr) {
	ByteBuffer wrap = ByteBuffer.wrap(bArr);
	wrap.order(ByteOrder.LITTLE_ENDIAN);
	BleAuthenticationData bleAuthenticationData = new BleAuthenticationData();
	try {
		bleAuthenticationData.setStage(wrap.get());
		byte[] bArr2 = new byte[8];
		wrap.get(bArr2);
		bleAuthenticationData.setNonce(bArr2);
		byte[] bArr3 = new byte[8];
		wrap.get(bArr3);
		bleAuthenticationData.setDeviceId(bArr3);
		return bleAuthenticationData;
	} catch (Throwable th) {
		C5323b.m11957a(f15488a, "byte array parse error", th);
		return null;
	}
}

/* renamed from: a */
public static byte[] m12025a(BleAuthenticationData bleAuthenticationData) {
	ByteBuffer allocate = ByteBuffer.allocate(17);
	allocate.order(ByteOrder.LITTLE_ENDIAN);
	try {
		allocate.put(bleAuthenticationData.getStage());
		allocate.put(bleAuthenticationData.getNonce());
		allocate.put(bleAuthenticationData.getDeviceId());
		return allocate.array();
	} catch (Throwable th) {
		C5323b.m11957a(f15488a, "BleAuthenticationData parse error", th);
		return null;
	}
}
```

Here the `BleAuthenticationData` is a simple container class, but it does
define some useful constants:

```java
public static final int DEVICE_ID_LENGTH = 8;
public static final int NONCE_LENGTH = 8;
public static final byte STAGE_1 = 1;
public static final byte STAGE_2 = 2;
public static final byte STAGE_3 = 3;
public static final byte STAGE_4 = 4;
```

This suggests there should be 17 bytes exchanged total, and it is confirmed by
the HCI logs too. Here are two successful 3-way handshakes, performed by the
app:

| Direction       | Data                                   |
|-----------------|----------------------------------------|
| Phone -> Camera | `01 480a18d127efee42 8457d5704c2be553` |
| Camera -> Phone | `02 0000626300006764 357ed673c4281573` |
| Phone -> Camera | `03 480a18d127efee42 988f74040e99ffc2` |


| Direction       | Data                                   |
|-----------------|----------------------------------------|
| Phone -> Camera | `01 0bb2f119679250af 8457d5704c2be553` |
| Camera -> Phone | `02 000061730000589e cedf128b01214348` |
| Phone -> Camera | `03 0bb2f119679250af c5daf56728f5c358` |

The device ID sent by the phone during the two sessions is the same, although
that does not need to be true. Also the nonce sent by the phone in stages 1 and
3 is the same.

The actual low-level logic is implemented in a JNI class, wrapped in `jniLsSec`,
as seen in `com/nikon/LsSec/jniLsSec.java`:

```java
public class jniLsSec {
    static {
        System.loadLibrary("LsSec-jni");
    }

    public native int Decipher(byte[] bArr, byte[] bArr2, char c, boolean z);

    public native int Encipher(byte[] bArr, byte[] bArr2, char c, boolean z);

    public native int GenerateKey(byte[] bArr, byte[] bArr2, boolean z);

    public native int GetContextData(byte[] bArr, byte[] bArr2, byte[] bArr3, byte[] bArr4, long[] jArr, long[] jArr2, int[] iArr, boolean z);

    public native int SetContextData(byte[] bArr, byte[] bArr2, byte[] bArr3, byte[] bArr4, long[] jArr, long[] jArr2, int i, boolean z);

    public native int Stage1st(byte[] bArr);

    public native int Stage3rd(byte[] bArr, byte[] bArr2, byte[] bArr3, byte[] bArr4);

    public native int init(int i, boolean z);
}
```

This class is then wrapped in yet another Java wrapper, in
`com/nikon/snapbridge/cmru/backend/data/repositories/camera/connection/p246a/C3573g.java`:

```java
/* renamed from: com.nikon.snapbridge.cmru.backend.data.repositories.camera.connection.a.g */
public final class C3573g implements AbstractC3577c {

    /* renamed from: a */
    public final jniLsSec f9974a = new jniLsSec();

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret, com.nikon.snapbridge.cmru.ptpclient.actions.connections.ConnectBluetoothAction.SecretCreator
    public final byte[] decode(byte[] bArr) {
        byte[] bArr2 = new byte[bArr.length];
        this.f9974a.Decipher(bArr, bArr2, (char) bArr.length, false);
        return bArr2;
    }

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret
    public final byte[] encode(byte[] bArr) {
        byte[] bArr2 = new byte[bArr.length];
        this.f9974a.Encipher(bArr, bArr2, (char) bArr.length, false);
        return bArr2;
    }

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret, com.nikon.snapbridge.cmru.ptpclient.actions.connections.ConnectBluetoothAction.SecretCreator
    public final int generateKey(byte[] bArr, byte[] bArr2) {
        return this.f9974a.GenerateKey(bArr, bArr2, false);
    }

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret, com.nikon.snapbridge.cmru.ptpclient.actions.connections.ConnectBluetoothAction.SecretCreator
    public final int getContextData(byte[] bArr, byte[] bArr2, byte[] bArr3, byte[] bArr4, long[] jArr, long[] jArr2, int[] iArr, boolean z) {
        return this.f9974a.GetContextData(bArr, bArr2, bArr3, bArr4, jArr, jArr2, iArr, z);
    }

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret, com.nikon.snapbridge.cmru.ptpclient.actions.connections.ConnectBluetoothAction.SecretCreator
    public final void init(int i) {
        this.f9974a.init(i, false);
    }

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret, com.nikon.snapbridge.cmru.ptpclient.actions.connections.ConnectBluetoothAction.SecretCreator
    public final int setContextData(byte[] bArr, byte[] bArr2, byte[] bArr3, byte[] bArr4, long[] jArr, long[] jArr2, int i, boolean z) {
        return this.f9974a.SetContextData(bArr, bArr2, bArr3, bArr4, jArr, jArr2, i, z);
    }

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret, com.nikon.snapbridge.cmru.ptpclient.actions.connections.ConnectBluetoothAction.SecretCreator
    public final byte[] stage1() {
        byte[] bArr = new byte[8];
        this.f9974a.Stage1st(bArr);
        return bArr;
    }

    @Override // com.nikon.snapbridge.cmru.bleclient.IBleLssSecret, com.nikon.snapbridge.cmru.ptpclient.actions.connections.ConnectBluetoothAction.SecretCreator
    public final byte[] stage3(byte[] bArr, byte[] bArr2, byte[] bArr3) {
        byte[] bArr4 = new byte[8];
        this.f9974a.Stage3rd(bArr, bArr2, bArr3, bArr4);
        return bArr4;
    }
}
```

The JNI implementation lives in `libLsSec-jni.so`, which the APK bundles for
four architectures, `x86`, `x86_64`, `armeabi-v7a` and `arm64-v8a`.

The entry point is the `init()` function, which is called from Java, where `i`
is set to the current time in millis, and `z` is always set to false:

1. `this.f15246d.init((int) System.currentTimeMillis());`
2. `this.f9974a.init(i, false);`

The actual low-level `Java_com_nikon_LsSec_jniLsSec_init()` function basically
just calls `LsSecInit()`. The full disassembled `x86_64` file is
[available here](https://onlinedisassembler.com/odaweb/XRK2gmox).

```
00000000000023d0 <Java_com_nikon_LsSec_jniLsSec_init@@Base>:
    23d0:       80 f9 01                cmp    $0x1,%cl
    23d3:       48 63 f2                movslq %edx,%rsi
    23d6:       74 10                   je     23e8 <Java_com_nikon_LsSec_jniLsSec_init@@Base+0x18>
    23d8:       48 8d 3d a1 8d 00 00    lea    0x8da1(%rip),%rdi        # b180 <__bss_start@@Base+0x2170>
    23df:       e9 fc e8 ff ff          jmp    ce0 <LsSecInit@@Base>
    23e4:       0f 1f 40 00             nopl   0x0(%rax)
    23e8:       48 8d 3d 91 ae 00 00    lea    0xae91(%rip),%rdi        # d280 <__bss_start@@Base+0x4270>
    23ef:       e9 ec e8 ff ff          jmp    ce0 <LsSecInit@@Base>
    23f4:       66 66 66 2e 0f 1f 84    data16 data16 cs nopw 0x0(%rax,%rax,1)
    23fb:       00 00 00 00 00
```

Reconstructing that to C, we get the following ugly-looking code:

```c
int __cdecl Java_com_nikon_LsSec_jniLsSec_init(int a1, int a2, unsigned int a3, char a4)
{
  int result; // eax

  if ( a4 == 1 )
    result = LsSecInit(&unk_9200, a3);
  else
    result = LsSecInit(&unk_8140, a3);
  return result;
}
```

Knowing that this is JNI, we can further clean it up:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_init(JNIEnv *env, jobject thisobj, jint i, jboolean z) {
  if (z == JNI_TRUE) {
    return LsSecInit(&unk_9200, seed);
  }
  return LsSecInit(&unk_8140, seed);
}
```

And since we know that `z` is always false in our case, we can simply translate
this to a call to `LsSecInit(&unk_8140, seed)`.

The next step is to decompile `LsSecInit()`. Jumping straight to the C code
this time, it looks rather complicated at first:

```c
#include <stdint.h>
#include <x86intrin.h>

int __cdecl LsSecInit(__m128i *a1, unsigned int seed)
{
  __m128i *v2; // eax

  v2 = a1;
  do
  {
    _mm_storeu_si128(v2, (__m128i)0LL);
    ++v2;
  }
  while ( v2 != &a1[264] );
  a1[264].m128i_i8[0] = 0;
  a1[264].m128i_i8[1] = 0;
  a1[264].m128i_i8[2] = 0;
  a1[264].m128i_i8[3] = 0;
  a1[264].m128i_i8[4] = 0;
  a1[264].m128i_i8[5] = 0;
  a1[264].m128i_i8[6] = 0;
  a1[264].m128i_i8[7] = 0;
  a1[264].m128i_i8[8] = 0;
  a1[264].m128i_i8[9] = 0;
  a1[264].m128i_i8[10] = 0;
  a1[264].m128i_i8[11] = 0;
  if ( seed )
    srand(seed);
  sub_880();
  a1[264].m128i_i32[2] = 1;
  return 0;
}

uint32_t uint32_7040;

void sub_880() {
    uint32_7040 = 1;
}
```

However, what's really happening here is that the generated machine code is
using intrinsics to zero out a block of memory in 128-bit increments, and then
some padding. To simplify that, we can simply zero-out the array at
initilaisation time, like so:

```c
typedef int32_t ls_sec_data_t[265*128/32];

void LsSecInit(ls_sec_data_t arg, unsigned int seed) {
  srand(seed);
  arg[264*4 + 2] = 1;
}

int main() {
  // […]
  ls_sec_data_t ls_sec_data = {0};  // initialise to zeros here
  LsSecInit(ls_sec_data, now_millis_trunc);

  return 0;
}
```

But in reality, we don't really need to set those values until we stumble upon
some code that will actually use them. So for all intents and purposes, we
might as well just call `srand(now_millis_truc)`. And since all it does is sets
up the RNG, we don't need to care about truncating and whatnot; simply passing
any readily available time value should be good enough.

So next we look at `Java_com_nikon_LsSec_jniLsSec_Stage1st()`. Here is the
decompiled C code:

```c
int __cdecl Java_com_nikon_LsSec_jniLsSec_Stage1st(int a1, int a2, int a3)
{
  int v3; // ebp
  signed int v4; // ST1C_4
  char v6; // [esp+2Fh] [ebp-1Dh]

  v3 = (*(int (__cdecl **)(int, int, char *))(*(_DWORD *)a1 + 736))(a1, a3, &v6);
  v4 = LsSec1stStage((int)&unk_8140, v3);
  (*(void (__cdecl **)(int, int, int, _DWORD))(*(_DWORD *)a1 + 768))(a1, a3, v3, 0);
  return v4;
}
```

Again, looks overly complicated, but knowing this is JNI, we can rewrite the
function signature like so:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_Stage1st(JNIEnv *env, jobject thisobj, jbyteArray arr) {
  // […]
}
```

Inside the function, most of the magic is `GetByteArrayElements()` and probably
`GetByteArrayElements()`. Then the actual work is done in `LsSec1stStage()`,
which gets a pointer to our familiar address in memory, `&unk_8140`, as well as
`v3`, disguised as an int but really, a pointer into what is essentially eight
bytes of allocated memory.

Looking at `LsSec1stStage`, we see that it simply uses `rand()` to get two
integers and assign it to the addresses `v3` and `v3+4`, i.e. it generates
eight random bytes, then the Java code uses that to set the nonce value via
`setNonce()`. We don't really need to do all of this in C, so we'll jump right
to the next step, which in our case is `stage3`.

Here the deal is similar as with stage 1, except we have 3 arrays instead of
just one. Those three arrays all get converted from `jbyteArray` to `int`
(`char` arrays under the hood), and then back.

We can see from the Java code, that the arrays are:

1. The nonce.
2. Value we got previously from stage 1.
3. The device ID.

NOTE: (1) and (3) in this case are actually the nonce and device ID we got from
the camera.

Here is the decompiled C code, unmodified:

```c
signed int __cdecl LsSec3rdStage(int a1, int a2, int a3, int a4, int a5)
{
  int v5; // edx
  char *v6; // ebp
  int v7; // esi
  int v8; // edi
  int v10; // [esp+14h] [ebp-28h]

  if ( *(_DWORD *)(a1 + 4232) != 3 )
    return -103;
  sub_1B40(a1 + 32, a2, 8);
  sub_1B40(a1 + 40, a3, 8);
  sub_1B40(a1, a2, 4);
  sub_1B40(a1 + 4, a3, 4);
  v5 = 0;
  v6 = (char *)&unk_4200;
  v7 = a1 + 24;
  v8 = a1 + 8;
  while ( 1 )
  {
    v10 = v5;
    sub_1B40(v7, v6, 8);
    sub_8C0(v7, v8, 24);
    if ( !sub_1D00(v8, a4, 8) )
      break;
    v5 = v10 + 1;
    v6 += 8;
    if ( (_WORD)v10 == 7 )
      return -102;
  }
  *(_BYTE *)a1 = v10;
  sub_1B40(a1 + 32, a3, 8);
  sub_1B40(a1 + 40, a2, 8);
  sub_8C0(v7, a5, 24);
  *(_DWORD *)(a1 + 4232) = 5;
  return 0;
}
```

## Repro Instructions

To repro the next steps, run this (preferrably in a container):

1. Download `SnapBridge_v2.8.3.apk` from apkpure.com.
2. Extract using `jadx --deobf SnapBridge_v2.8.3.apk`.
3. Create a C file `jni_test.c` containing this test case:

```c
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>


int Java_com_nikon_LsSec_jniLsSec_init(int, bool);

int main() {
  /* JAVA:
  final long now_millis = System.currentTimeMillis();
  final int now_millis_trunc = (int) now_millis;

  System.out.printf("now_millis: %d\n", now_millis);
  System.out.printf("now_millis_trunc: %d\n", now_millis_trunc);
  */

  struct timeval t;
  gettimeofday(&t, NULL);

  const long now_millis = (t.tv_sec * 1000) + t.tv_usec;
  const int now_millis_trunc = (int) now_millis;

  printf("now_millis: %lu\n", now_millis);
  printf("now_millis_trunc: %d\n", now_millis_trunc);

  const int res = Java_com_nikon_LsSec_jniLsSec_init(now_millis_trunc, false);
  printf("res: %d\n", res);

  return 0;
}
```

Then compile using Clang:

```sh
$ clang jni_test.c -o jni_test -L./SnapBridge_v2.8.3/resources/lib/x86_64 -lLsSec-jni
```

---

Note that a similar protocol is described in
[this paper](https://eprint.iacr.org/2009/013.pdf#page=13), on page 13.
