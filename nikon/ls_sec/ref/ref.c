// rand(), srand()
#include <stdlib.h>
#include <emmintrin.h>

#include "code/defs.h"

#define _OWORD __uint128_t
#define _byteswap_ulong __bswap_64

#define __ptr_to_addr_space(__addr_space_nbr, __type, __offset)              \
    ((volatile __type __attribute__((__address_space__(__addr_space_nbr)))*) \
    (__offset))


unsigned __int64 __readfsqword(unsigned long);
unsigned __int64 __readfsqword(unsigned long __offset) {
  return *__ptr_to_addr_space(257, unsigned __int64, __offset);
}

__int64 __fastcall LsSecInit(_BYTE *, __int64);

static _BYTE byte_4AC0[64] = {
  //; DATA XREF: LsSec2ndStage+74↑o
  //; LsSec4thStage+14↑o ...
  0x70, 0x40, 0x66, 0x0E4, 0x4, 33, 0x0D5, 0x52, 0x0ED, 0x4B, 0x8F,
  0x0AC, 0x15, 0x0F7, 0x0E4, 0x7B, 0x24, 0x47, 0x1F, 0x11, 0x8B,
  0x5E, 0x0A1, 0x0FC, 0x5, 96, 0x0C, 0x31, 0x2B, 0x8C, 0x7F, 0x41,
  0x0FD, 0x0A5, 0x88, 0x0C1, 0x0EB, 0x0A8, 0x0B1, 0x0F3, 0x99,
  0x16, 0x60, 0x56, 0x1B, 0x0D3, 0x0D5, 0x50, 0x0CD, 0x32, 0x68,
  0x7F, 0x0A9, 0x0E2, 0x8A, 0x30, 0x2A, 0x8F, 0x0E8, 0x34, 0x0DE,
  0x0C7, 0x0EB, 0x0F4,
};

static _DWORD dword_2A00[2096] = {
//; DATA XREF: sub_A80+A1↑o
//; sub_A80+1CC↑o
0x0E813EC15, 0, 0x0AE5B6CEA, 0, 0x6CA89E35, 0, 0x4CF05207,
0, 0x4806AD72, 0, 0x0D5FDB061, 0, 0x0C7FD55E4, 0, 0x46B160BE,
0, 0x82AB1888, 0, 0x6F1C061F, 0, 0x0B9ED5302, 0, 0x5391939,
0, 0x93D86FFC, 0, 0x9C8B78FE, 0, 0x0C51FF235, 0, 0x8CEE7883,
0, 0x96EA497E, 0, 0x7C3F81CA, 0, 0x349A3164, 0, 0x85CABA9F,
0, 0x925C3EC, 0, 0x4DFC20DB, 0, 0x66BCF8C7, 0, 0x0C49CFFF2,
0, 0x23F8A60A, 0, 0x1836ED57, 0, 0x5319D2D8, 0, 0x6A3E2B3C,
0, 0x0B1750EA3, 0, 0x5E90F08B, 0, 0x79AF2149, 0, 0x4DB554BA,
0, 0x2F693364, 0, 0x0F3E79DB, 0, 0x0FBDBDA72, 0, 0x8C5E1023,
0, 0x9B8A1D2A, 0, 0x0A08D493B, 0, 0x60ECC378, 0, 0x3EDB5E91,
0, 0x0E63AD392, 0, 0x4763C490, 0, 0x699D4F35, 0, 0x3A4C6B8C,
0, 0x0ECEEDF98, 0, 0x921874A2, 0, 0x2C3B75F0, 0, 0x0C8A94DD8,
0, 0x9AEACD32, 0, 0x4CD1473F, 0, 0x0FF5DD017, 0, 0x1355CCFB,
0, 0x0A4DF6FAC, 0, 0x0D6946E66, 0, 0x93DEB1F7, 0, 0x5BA1A1E6,
0, 0x0AF8D3210, 0, 0x0F58339AF, 0, 0x19C9137B, 0, 0x45AB1745,
0, 0x27BE2C3, 0, 0x0FEBD204, 0, 0x0EF573E02, 0, 0x82FBA559,
0, 0x966D9750, 0, 0x0C75F6E48, 0, 0x5D117A62, 0, 0x0DA8401E,
0, 0x555E573E, 0, 0x0FCD4CEBD, 0, 0x6EEE9752, 0, 0x2E416589,
0, 0x8F4E5731, 0, 0x226EF4A5, 0, 0x0F113DF59, 0, 0x182DC602,
0, 0x6CAC7390, 0, 0x3CD7186C, 0, 0x0A9C5C36, 0, 0x1262446E,
0, 0x0F73E2142, 0, 0x0A6CDE914, 0, 0x0FF8835F0, 0, 0x0DE28B148,
0, 0x0F4D97681, 0, 0x0C47B135B, 0, 0x6C94445E, 0, 0x74699309,
0, 0x0F5180902, 0, 0x5C3DCF47, 0, 0x6826ED46, 0, 0x98F618A2,
0, 0x5882D78A, 0, 0x6B9EA708, 0, 0x0A5FB9553, 0, 0x0C7848225,
0, 0x634FAD1B, 0, 0x573D14BF, 0, 0x9CAECDB5, 0, 0x0C63D0AF5,
0, 0x9E9AC886, 0, 0x0A9605A3A, 0, 0x0B2B96D6F, 0, 0x84B6D2EA,
0, 0x25D1E734, 0, 0x0BF097443, 0, 0x0A633DB5E, 0, 0x0E75E356F,
0, 0x184CDAEF, 0, 0x2880982A, 0, 0x0F8F54F27, 0, 0x0AAEEB8D9,
0, 0x0B7571672, 0, 0x431D70BC, 0, 0x0CDF825F1, 0, 0x0AB4D334C,
0, 0x1F107369, 0, 0x33FE0685, 0, 0x0CC51AA54, 0, 0x4AF76E6F,
0, 0x0FAA6984B, 0, 0x0C39E8EA3, 0, 0x5823E67A, 0, 0x63EE6300,
0, 0x10AC0464, 0, 0x0E384D9EE, 0, 0x3D27D4FD, 0, 0x7441B6E6,
0, 0x29C815B5, 0, 0x55732B19, 0, 0x1103C32D, 0, 0x82821CBE,
0, 0x0FAA06A0A, 0, 0x0A6CFAD30, 0, 0x0F97AC0B0, 0, 0x1197DA41,
0, 0x1AC332A5, 0, 0x0D7777520, 0, 0x0B78C649B, 0, 0x0A5F76B4E,
0, 0x0DE7E8F98, 0, 0x0F410FBB0, 0, 0x8BF0F01, 0, 0x0EC880D6F,
0, 0x8AC457D6, 0, 0x5911D66C, 0, 0x0EC091705, 0, 0x0B43A07E7,
0, 0x0DB463B42, 0, 0x7D79D6F1, 0, 0x7753FB09, 0, 0x358D77FA,
0, 0x430E4767, 0, 0x41E32293, 0, 0x1505050A, 0, 0x13B599A9,
0, 0x0D12FF07D, 0, 0x4DE5E72A, 0, 0x1B6BABEE, 0, 0x0C3E58FB5,
0, 0x8CD9FFCE, 0, 0x3A031286, 0, 0x0C9ED35C3, 0, 0x61D54C65,
0, 0x0EC538477, 0, 0x8A0B44FD, 0, 0x85C12CDE, 0, 0x9C1649D9,
0, 0x34226DEE, 0, 0x74C363D, 0, 0x0DA45157C, 0, 0x0D90BD7C0,
0, 0x3EF8FF7A, 0, 0x0E4769568, 0, 0x0A7E35774, 0, 0x5D62F204,
0, 0x3EA9CBBC, 0, 0x84B88FA6, 0, 0x3B0E0457, 0, 0x75DBC341,
0, 0x0E91406B1, 0, 0x85B76900, 0, 0x0F447FE6A, 0, 0x1D12ABB2,
0, 0x0C73DE105, 0, 0x71B4BC02, 0, 0x0BA37BD26, 0, 0x8D3B3C00,
0, 0x3328905B, 0, 0x0B39BDFBB, 0, 0x0DEBFE7A9, 0, 0x5CA2DB5F,
0, 0x7713B03C, 0, 0x0A1D96145, 0, 0x0B013F0A8, 0, 0x0E026DCF5,
0, 0x98BB36A3, 0, 0x0AFC61518, 0, 0x881B1096, 0, 0x0F2EEEEAD,
0, 0x2BE4CC7D, 0, 0x9122D501, 0, 0x6612270D, 0, 0x4FEBE6E,
0, 0x8ED69D68, 0, 0x250B014, 0, 0x0ACA682BB, 0, 0x45ACDC97,
0, 0x0D82CEAFC, 0, 0x48E1F4AB, 0, 0x0AD6CE580, 0, 0x5E906D8,
0, 0x9E1A160A, 0, 0x6608F9D, 0, 0x7F35342C, 0, 0x0C0EB0EB5,
0, 0x3C3A792, 0, 0x0BA2E19DB, 0, 0x0EAA3D476, 0, 0x0AA9E8BF7,
0, 0x79C3A3CF, 0, 0x0FD51D0BC, 0, 0x0B2FE6A84, 0, 0x371703A2,
0, 0x7D098D09, 0, 0x7E5B556A, 0, 0x0D1F18C0, 0, 0x44D6C102,
0, 0x0D451F8AD, 0, 0x593BA6AC, 0, 0x0F9F0F691, 0, 0x9780793,
0, 0x71DB07D8, 0, 0x0EB65EA, 0, 0x1445FC15, 0, 0x0C9D8A601,
0, 0x96050CF1, 0, 0x0A4F5B71C, 0, 0x0DCD4EE03, 0, 0x8E61BB7C,
0, 0x851E700A, 0, 0x21E918E3, 0, 0x13E21F51, 0, 0x7719484D,
0, 0x0FA4DB14, 0, 0x0DB70EBCD, 0, 0x54B14C0C, 0, 0x1F0C3A3E,
0, 0x0AF90B083, 0, 0x74FF445D, 0, 0x0A7D0A611, 0, 0x687F8285,
0, 0x0C403DC1C, 0, 0x98B8FC11, 0, 0x9D13DFE2, 0, 0x0F27CDD7C,
0, 0x8334CF1D, 0, 0x0C38D7398, 0, 0x56D87A93, 0, 0x6EE70D0D,
0, 0x650FAC36, 0, 0x0D4529EB0, 0, 0x0CA81379E, 0, 0x4155F31,
0, 0x806E4DAB, 0, 0x0FBEC7589, 0, 0x61160A64, 0, 0x4A1E0FEC,
0, 0x0EED49950, 0, 0x3E14B39E, 0, 0x7974438A, 0, 0x0F265621A,
0, 0x0D0736E87, 0, 0x980DC594, 0, 0x0EF0172FE, 0, 0x0ACF1C9ED,
0, 0x7825B08E, 0, 0x94FFA2F2, 0, 0x0C9289426, 0, 0x0D5644FE7,
0, 0x28A399D9, 0, 0x0B62E783F, 0, 0x0E302F037, 0, 0x0F373F9F4,
0, 0x7B36B756, 0, 0x0BC2CF053, 0, 0x3AA190DB, 0, 0x0C86EF2AD,
0, 0x0C58F48BF, 0, 0x94C3737B, 0, 0x0DBB4581E, 0, 0x325063E,
0, 0x528AE3BC, 0, 0x9F3E8E41, 0, 0x40A352F0, 0, 0x0BB7B4CDE,
0, 0x51B55266, 0, 0x854279F5, 0, 0x0AEF100A4, 0, 0x165BC082,
0, 0x950F255D, 0, 0x3D5B31A, 0, 0x2387DE20, 0, 0x5A8C182F,
0, 0x34A6C854, 0, 0x91C44DC0, 0, 0x0A2D4834D, 0, 0x348376E,
0, 0x0B01EA24E, 0, 0x21C23C8F, 0, 0x0F2A4E82F, 0, 0x4A2FABF,
0, 0x8431B727, 0, 0x0EC4D9B29, 0, 0x0A61BEDA8, 0, 0x3DF73976,
0, 0x1D3ED935, 0, 0x4AD99648, 0, 0x62F30DC0, 0, 0x5EB2B7FC,
0, 0x0AAD2133B, 0, 0x89320EA2, 0, 0x0A16FF8D7, 0, 0x0F03D9403,
0, 0x44D376E7, 0, 0x6C5EEB26, 0, 0x2F8B0FDA, 0, 0x0C4D9CD3B,
0, 0x0F598252, 0, 0x0E9D0E431, 0, 0x0B9487338, 0, 0x0C3575A00,
0, 0x444C21E, 0, 0x0A8684A8E, 0, 0x0B7D32FFD, 0, 0x0D82E0476,
0, 0x9E53D126, 0, 0x686C68C3, 0, 0x5AEE3695, 0, 0x297AC263,
0, 0x0C7D8593, 0, 0x73D0BBA0, 0, 0x0F45F6FD0, 0, 0x0D04BFE25,
0, 0x5A202CE3, 0, 0x3C0CED5, 0, 0x7E9932B8, 0, 0x55FF6D39,
0, 0x0F8F659E9, 0, 0x93C8BCA3, 0, 0x96A2EBA8, 0, 0x0E6C1E9AA,
0, 0x62FF40CB, 0, 0x646F808E, 0, 0x949404C2, 0, 0x0A56664C9,
0, 0x0B54F8CDB, 0, 0x8CD633EE, 0, 0x0B5F1E7A9, 0, 0x3C9868FE,
0, 0x85ECD3E6, 0, 0x1D9C7A5E, 0, 0x28D76CFD, 0, 0x43DC2ECC,
0, 0x0CA7C030A, 0, 0x77015619, 0, 0x0A80E8C4A, 0, 0x32223D76,
0, 0x9A0B6E9F, 0, 0x0F6C86142, 0, 0x4F08A782, 0, 0x9160F535,
0, 0x5C181FC1, 0, 0x0FF08632, 0, 0x0D6F1E693, 0, 0x3E91BCD0,
0, 0x0A8C192CD, 0, 0x0EB8BD294, 0, 0x2E2C34DF, 0, 0x0AD9270BC,
0, 0x0E7C11F13, 0, 0x6B1B97B2, 0, 0x0DDF0916E, 0, 0x0C52EE357,
0, 0x9424B93B, 0, 0x3F1B9C4E, 0, 0x8A86281E, 0, 0x0CFFB5111,
0, 0x992E4BE3, 0, 0x5FDE8E86, 0, 0x429164C8, 0, 0x5B91457D,
0, 0x2D117B86, 0, 0x4B206DF9, 0, 0x2BCA39C4, 0, 0x0F3C368DD,
0, 0x0FC503CDA, 0, 0x17A43178, 0, 0x477570F6, 0, 0x29469B54,
0, 0x755D0C3C, 0, 0x257D4BE7, 0, 0x3E9726A7, 0, 0x0C5D37553,
0, 0x4BBEF76A, 0, 0x73B093CD, 0, 0x6C42388C, 0, 0x0B9B93F9A,
0, 0x2B509077, 0, 0x157B5407, 0, 0x316D8887, 0, 0x0C8A333F0,
0, 0x26408830, 0, 0x88406018, 0, 0x178C25D1, 0, 0x5E2E6485,
0, 0x17AE0C1A, 0, 0x1D3056A6, 0, 0x8A40A6EB, 0, 0x0AEDF615E,
0, 0x76C61F07, 0, 0x61AFFF4B, 0, 0x0C8B19F84, 0, 0x0A8DD031D,
0, 0x32ED1E04, 0, 0x650E7A54, 0, 0x3F355046, 0, 0x416154C1,
0, 0x4B42F507, 0, 0x4F99E501, 0, 0x97944470, 0, 0x0CFFF06CA,
0, 0x2DE248DF, 0, 0x36EA2F54, 0, 0x0B1315C, 0, 0x5DB6E50B,
0, 0x0E57A5E82, 0, 0x58E79671, 0, 0x0B096BB7E, 0, 0x0D9468647,
0, 0x9E8A408B, 0, 0x0FA2A736D, 0, 0x0AB5404C9, 0, 0x0C0C96E14,
0, 0x82655A1E, 0, 0x822D97C5, 0, 0x0DD9C9E7F, 0, 0x34CADCF6,
0, 0x0C0EFAC61, 0, 0x0A2F3837C, 0, 0x36C5BCF9, 0, 0x0E1934DD1,
0, 0x0B2BF8A31, 0, 0x761738AE, 0, 0x0E31D1DF2, 0, 0x7AA84C10,
0, 0x0AE5E7F5E, 0, 0x0A360A5, 0, 0x0C2A9D757, 0, 0x1AC28895,
0, 0x0B963F750, 0, 0x88B58ED5, 0, 0x0D3C6D19E, 0, 0x606CC514,
0, 0x0D579A905, 0, 0x0AA28315B, 0, 0x3A93F01A, 0, 0x4D29F540,
0, 0x0C8F59A8D, 0, 0x0E71957EA, 0, 0x2D9F3769, 0, 0x0B6F415B5,
0, 0x99C8882D, 0, 0x504B0E36, 0, 0x2BF12F0B, 0, 0x0F90C2648,
0, 0x61A385D, 0, 0x1195DD23, 0, 0x62B00207, 0, 0x2BCBF4F3,
0, 0x70887523, 0, 0x9F9E51B1, 0, 0x9A212242, 0, 0x928EF16A,
0, 0x9BE547CD, 0, 0x716752F8, 0, 0x0D70D7E99, 0, 0x8D4F14CD,
0, 0x448A4AED, 0, 0x5BAEE03C, 0, 0x0EA8B8DE6, 0, 0x5CC62978,
0, 0x0F84C10AD, 0, 0x78E7D28F, 0, 0x0E2D6EB3A, 0, 0x0BC05A25E,
0, 0x7699FD62, 0, 0x468A77A8, 0, 0x0FAEE0313, 0, 0x388C2572,
0, 0x8728DEEC, 0, 0x0C2F7D131, 0, 0x2F66BFBE, 0, 0x0C34EA214,
0, 0x0EE452308, 0, 0x0E9144DA5, 0, 0x2E1EB77F, 0, 0x478B94DC,
0, 0x0A5250804, 0, 0x1063CFAB, 0, 0x4A8F7F12, 0, 0x5E354B01,
0, 0x883D4B4B, 0, 0x0B558639, 0, 0x0F5513B36, 0, 0x0C14278,
0, 0x0B46DE83A, 0, 0x5859D16D, 0, 0x249E95AA, 0, 0x959C2676,
0, 0x0BF54A4AC, 0, 0x0AF3B032B, 0, 0x53C02913, 0, 0x9BE1F5E6,
0, 0x16CA7628, 0, 0x0CE5290BB, 0, 0x0E1285AA4, 0, 0x72B8751A,
0, 0x0FC1AC1CE, 0, 0x761BA2E8, 0, 0x0EF84551F, 0, 0x27979ACE,
0, 0x80EC9A85, 0, 0x0C6BA7211, 0, 0x27F67513, 0, 0x0A647E047,
0, 0x0D6324AD2, 0, 0x90A8FD9C, 0, 0x9020980E, 0, 0x3B622AE9,
0, 0x1894C4C2, 0, 0x8744F86B, 0, 0x9E81668F, 0, 0x12A0C3FE,
0, 0x0B06CE63B, 0, 0x0A9AD70E, 0, 0x0F03726DA, 0, 0x7C697704,
0, 0x2BEC9A6A, 0, 0x0F23E3E81, 0, 0x0CA9E6D20, 0, 0x2AB584A2,
0, 0x95F8906F, 0, 0x0EA569F3B, 0, 0x0E4B3ECA6, 0, 0x34F4F597,
0, 0x53CC8E97, 0, 0x61D5986C, 0, 0x0E820E355, 0, 0x90BDEEF4,
0, 0x95346C71, 0, 0x8ED352C3, 0, 0x0A50517F8, 0, 0x841D4DC1,
0, 0x93C4893D, 0, 0x60E56A4F, 0, 0x0DBE1448, 0, 0x0C0C9BD0C,
0, 0x5F70A73E, 0, 0x816D2706, 0, 0x0C1712CC1, 0, 0x2129A7F2,
0, 0x473887F3, 0, 0x0B049471A, 0, 0x34E7E699, 0, 0x7568D07F,
0, 0x0A274B682, 0, 0x43788AA5, 0, 0x0CEB15929, 0, 0x0D98A06A5,
0, 0x0D252426E, 0, 0x82338F82, 0, 0x0AEC1CBD9, 0, 0x0A17AF214,
0, 0x7C3DFF3D, 0, 0x80862C, 0, 0x0D688FFAE, 0, 0x0C1FA8A40,
0, 0x146FB554, 0, 0x0AD0BBEEB, 0, 0x0AEF8E4F4, 0, 0x2B5D0E80,
0, 0x0F7F62436, 0, 0x0B11C30BF, 0, 0x395C8FA9, 0, 0x65BCFD61,
0, 0x0CB1150DF, 0, 0x33410334, 0, 0x18B6880C, 0, 0x23F545AE,
0, 0x825AF6C4, 0, 0x62085128, 0, 0x8F9B0692, 0, 0x2D0589A5,
0, 0x46DDCA1B, 0, 0x9B9A2B26, 0, 0x0A2B164C9, 0, 0x3FE57A47,
0, 0x0A5859C3B, 0, 0x0FD1A3587, 0, 0x5D12C6C6, 0, 0x1FD6DF72,
0, 0x0C01BAA53, 0, 0x48B38489, 0, 0x1AF0D528, 0, 0x653978CE,
0, 0x66E651AD, 0, 0x93E1431D, 0, 0x4AC7E3DC, 0, 0x3672F4ED,
0, 0x1B6B47B0, 0, 0x52981A7B, 0, 0x0F9B23939, 0, 0x0A3D35A4B,
0, 0x4B051CA8, 0, 0x0D55F4988, 0, 0x0C90D551B, 0, 0x55052644,
0, 0x0AA0E5892, 0, 0x6E9466A2, 0, 0x0C5271935, 0, 0x5485D1BF,
0, 0x32CC1BD0, 0, 0x0F8B27AE1, 0, 0x54D58C98, 0, 0x0F0D4464,
0, 0x0D79561E4, 0, 0x471D8C65, 0, 0x0A4B7D9C3, 0, 0x7E02FBB1,
0, 0x0A4F62CF1, 0, 0x0B319378B, 0, 0x529AC147, 0, 0x0CDB9EC8C,
0, 0x0BB7C1977, 0, 0x0A965D184, 0, 0x5962299E, 0, 0x8A424D4D,
0, 0x0F5E414B2, 0, 0x0A7EEDAD0, 0, 0x272A7A2E, 0, 0x0F5F79CF2,
0, 0x7398ED00, 0, 0x8EEA759B, 0, 0x716F0D6A, 0, 0x2FA790C6,
0, 0x8D37B3E2, 0, 0x7476247B, 0, 0x96D64840, 0, 0x0CB36F40B,
0, 0x86134CD5, 0, 0x42ACC3CB, 0, 0x54687DE9, 0, 0x6F139188,
0, 0x0B8A7E69D, 0, 0x70D52CA8, 0, 0x950B8903, 0, 0x24F30040,
0, 0x0D9364A1F, 0, 0x9A489C4D, 0, 0x4D2C6573, 0, 0x36B0F1BD,
0, 0x0AC3E8D2F, 0, 0x0CBCA34AA, 0, 0x89CC9E13, 0, 0x0B57A9792,
0, 0x0F4B97EA6, 0, 0x7F40CAFF, 0, 0x41E06B8F, 0, 0x1DC8CA7,
0, 0x7047835D, 0, 0x0CAF06E07, 0, 0x0CE3166ED, 0, 0x461B02A6,
0, 0x986FFD82, 0, 0x994339E5, 0, 0x0ECCCE79D, 0, 0x0F8E94954,
0, 0x81845AC1, 0, 0x7041F2B3, 0, 0x0AEF81D26, 0, 0x80F66DF2,
0, 0x0EEB98066, 0, 0x0D7680496, 0, 0x0EB045D13, 0, 0x0ACD51786,
0, 0x0A6E88C37, 0, 0x0AC89550F, 0, 0x4CB76F7F, 0, 0x0B2C39471,
0, 0x0E7CFF429, 0, 0x62BFF472, 0, 0x2F48314B, 0, 0x6909EFA4,
0, 0x1601D60A, 0, 0x0ED86E1B1, 0, 0x56BC6BED, 0, 0x5E2E690B,
0, 0x1BDCB81D, 0, 0x9BA78896, 0, 0x0D14493D9, 0, 0x0CCC812E8,
0, 0x6A11C2F1, 0, 0x8F82CC4F, 0, 0x63C4DDB5, 0, 0x4604AF89,
0, 0x1958DC1B, 0, 0x0F45700D, 0, 0x4A0162EE, 0, 0x47963EF2,
0, 0x0F822CEA7, 0, 0x9E2781A5, 0, 0x0FABA2CB0, 0, 0x336C1882,
0, 0x0CAFC34AF, 0, 0x11A91377, 0, 0x0F7EC9131, 0, 0x9AD9DCFF,
0, 0x9051CE01, 0, 0x7E135E89, 0, 0x0E36E5442, 0, 0x1630D8A7,
0, 0x0F483609C, 0, 0x26A71FF6, 0, 0x0B3257181, 0, 0x22EBA3B7,
0, 0x2D5470E7, 0, 0x5BBEB076, 0, 0x0BCACB364, 0, 0x3A26A202,
0, 0x46E40370, 0, 0x0B5D74262, 0, 0x0E7FFC3AF, 0, 0x0F9C6A726,
0, 0x0B6EF19F5, 0, 0x456EFD1D, 0, 0x0A52210E0, 0, 0x74C91FB9,
0, 0x0E9408834, 0, 0x0C1F17CE7, 0, 0x944A79D2, 0, 0x87F17472,
0, 0x0BFC85D9A, 0, 0x99898B79, 0, 0x555F1352, 0, 0x9287F717,
0, 0x821B8505, 0, 0x9B675AA9, 0, 0x6C66FF79, 0, 0x0F48B87DF,
0, 0x9904484C, 0, 0x3E3861CC, 0, 0x0A0393660, 0, 0x0D7B8EA3A,
0, 0x55CBD010, 0, 0x0CA06470C, 0, 0x16AE9277, 0, 0x984178DA,
0, 0x0B777E797, 0, 0x0EF8173C9, 0, 0x56A3DE0C, 0, 0x64F350E9,
0, 0x0B2F54E0, 0, 0x896D4E6, 0, 0x246A097, 0, 0x4BD7FB97,
0, 0x0FA84F206, 0, 0x2BE66C3E, 0, 0x244930F4, 0, 0x0FCC2D994,
0, 0x9393570D, 0, 0x0AD0E9C60, 0, 0x35725AE2, 0, 0x0DE775BF7,
0, 0x0DBB87BC, 0, 0x0F8A5E82C, 0, 0x0D1A64E93, 0, 0x0D004558C,
0, 0x433C2996, 0, 0x0E14A5DAF, 0, 0x0C13E20BB, 0, 0x0FB5AC251,
0, 0x1FBD4BA2, 0, 0x7E414A5, 0, 0x754EF2D0, 0, 0x0F6E31444,
0, 0x6A350F7C, 0, 0x0B5F45341, 0, 0x0C8005AE8, 0, 0x903C0735,
0, 0x0B4487C1D, 0, 0x76411F84, 0, 0x0E3E2536, 0, 0x6B952D38,
0, 0x96750A94, 0, 0x0DC7AF26B, 0, 0x0D321B32C, 0, 0x20CC6,
0, 0x3BEB8B44, 0, 0x106486B7, 0, 0x0CAE518D3, 0, 0x1ACD54FD,
0, 0x0D90713E, 0, 0x97979922, 0, 0x0CDF948EC, 0, 0x0D567F27A,
0, 0x4F89BBBB, 0, 0x25D35AD7, 0, 0x0A328B965, 0, 0x930AC104,
0, 0x0BD126D37, 0, 0x1C16FD51, 0, 0x163015A6, 0, 0x8918C76C,
0, 0x0A68D6749, 0, 0x0AB3A9BE6, 0, 0x0C9CDB56A, 0, 0x50852BA,
0, 0x0A02344BE, 0, 0x96C8EA51, 0, 0x0AE2DB0FF, 0, 0x8526CB11,
0, 0x0D763BC51, 0, 0x85A06868, 0, 0x6B159FCC, 0, 0x0A975A4E3,
0, 0x0FAAC574E, 0, 0x0FA76B914, 0, 0x920A15C4, 0, 0x21DE09B2,
0, 0x0EACFF4D9, 0, 0x621EA993, 0, 0x0CFA5BF0A, 0, 0x0FA6123B3,
0, 0x0F4C65686, 0, 0x84F32CDF, 0, 0x0DE24ED75, 0, 0x5D594450,
0, 0x0C898562B, 0, 0x22E70FA0, 0, 0x0B9ADA330, 0, 0x891EEAD2,
0, 0x1CF520F9, 0, 0x3ED2ABB2, 0, 0x0A57B1527, 0, 0x0B616928A,
0, 0x0DFEA23AA, 0, 0x0E4EF20BC, 0, 0x99006D82, 0, 0x0B852A835,
0, 0x93E6AA74, 0, 0x0A0BCA025, 0, 0x0F9BA0440, 0, 0x0F60D2FE1,
0, 0x4AC3BFC4, 0, 0x0A6884182, 0, 0x45DD3563, 0, 0x543F95D9,
0, 0x7A9187A8, 0, 0x0A4CAC0B4, 0, 0x0D6DEA497, 0, 0x0EE7BDD29,
0, 0x3227A33C, 0, 0x2B1B249E, 0, 0x1D6AF45D, 0, 0x5546D960,
0, 0x0CF9F4289, 0, 0x15BBE6D3, 0, 0x69FCAE11, 0, 0x41D15DBB,
0, 0x0AA87AAFF, 0, 0x0DA2E36ED, 0, 0x324902DF, 0, 0x0AAC6326A,
0, 0x0A8A49066, 0, 0x9877E4FD, 0, 0x7F78C4EA, 0, 0x74DC2102,
0, 0x0F8352F71, 0, 0x96850CF, 0, 0x6C9267AD, 0, 0x9DE63A54,
0, 0x230E2D83, 0, 0x9441646E, 0, 0x41858B4D, 0, 0x0A4E2133D,
0, 0x8DB8071D, 0, 0x0BEAE6BC, 0, 0x1DE565B0, 0, 0x7A630757,
0, 0x8A192DA7, 0, 0x0CF66F778, 0, 0x149EF35, 0, 0x90E276B9,
0, 0x9FA45B04, 0, 0x83500842, 0, 0x0BA7ACF40, 0, 0x0A6F11455,
0, 0x13C23786, 0, 0x2F600CF3, 0, 0x0B9BA0E45, 0, 0x0B2DD471D,
0, 0x4B699AFB, 0, 0x6AAD4AF, 0, 0x36653DDB, 0, 0x0EAD16288,
0, 0x9D6E698C, 0, 0x6A150793, 0, 0x901735E1, 0, 0x1648714A,
0, 0x82A826E5, 0, 0x0D617E704, 0, 0x3075286, 0, 0x0CDF22348,
0, 0x0AD2F52F9, 0, 0x1F88DEA9, 0, 0x0A9D9FB50, 0, 0x81924438,
0, 0x0D74BE0F4, 0, 0x53707FCE, 0, 0x7037D954, 0, 0x30BB392F,
0, 0x983FFA5B, 0, 0x0FCF9AF16, 0, 0x9D223945, 0, 0x9CDC05A8,
0, 0x0B359DEF, 0, 0x0EE2BDB47, 0, 0x55593CA4, 0, 0x6525E8E1,
0, 0x50FBC4BB, 0, 0x29EA560C, 0, 0x359B0887, 0, 0x44B4DDFC,
0, 0x0A994D923, 0, 0x0A1E66DF6, 0, 0x8D584C54, 0, 0x552F957,
0, 0x0F4A27911, 0, 0x7AE967B8, 0, 0x17C94D94, 0, 0x431B5EA7,
0, 0x8B1089FA, 0, 0x95A94B43, 0, 0x0ECE3D707, 0, 0x0B59A5AFD,
0, 0x7AFCA1A2, 0, 0x42B47862, 0, 0x0B8031F68, 0, 0x0D54EDA3,
0, 0x0F4D78C68, 0, 0x7B4253FD, 0, 0x0A25CAD65, 0, 0x644828DE,
0, 0x2D112217, 0, 0x0C15A9F3D, 0, 0x7E8FF8FA, 0, 0x9469606,
0, 0x0C01F24C5, 0, 0x0CFFB6E4B, 0, 0x382E9C6E, 0, 0x6ACF8A9E,
0, 0x585DD9C3, 0, 0x0F94B801C, 0, 0x37B1578F, 0, 0x0C8C956EE,
0, 0x0E16EC6A8, 0, 0x1E9A491E, 0, 0x5C0F9305, 0, 0x7A452920,
0, 0x947F0327, 0, 0x1883A346, 0, 0x0DD69799, 0, 0x0E6246198,
0, 0x0E2543E43, 0, 0x31D1CBC7, 0, 0x4E81B6FC, 0, 0x58C07ECA,
0, 0x3F087B9E, 0, 0x3873748B, 0, 0x7E75E816, 0, 0x31AF1EE5,
0, 0x4CBCC3EE, 0, 0x7CF9D3D4, 0, 0x558F7981, 0, 0x0C47DB9DC,
0, 0x0D803BAF2, 0, 0x0EAB022FD, 0, 0x0AC06D1B9, 0, 0x305231EC,
0, 0x756F15B6, 0, 0x2DD7DD88, 0, 0x0D6A74A46, 0, 0x6B9E4141,
0, 0x0A5DBD4BA, 0, 0x0BBC274EA, 0, 0x8B66F111, 0, 0x85E18002,
0, 0x2D7B6928, 0, 0x91ECBC23, 0, 0x0C26A9150, 0, 0x52F4615C,
0, 0x79313F36, 0, 0x235C4E36, 0, 0x24EDFEA9, 0, 0x0DC8415E1,
0, 0x1E818A0D, 0, 0x1100272A, 0, 0x0CA22DA05, 0, 0x4894709,
0, 0x0B061A1F3, 0, 0x6874FDB9, 0, 0x0D09D8892, 0, 0x2E3E374A,
0, 0x8B99783E, 0, 0x47BD571D, 0, 0x584DE2F3, 0, 0x6AB7BAD2,
0, 0x279F0E56, 0, 0x0A969052F, 0, 0x0E006F6D, 0, 0x475A7246,
0, 0x8332126, 0, 0x0C5A08674, 0, 0x53650A95, 0, 0x8E869C35,
0, 0x24D3D138, 0, 0x0B5C01352, 0, 0x6533B0A6, 0, 0x5A6F42B0,
0, 0x9DA48984, 0, 0x4305FA01, 0x0D, 0,
};

static _DWORD dword_9040;

void sub_A50()
{
    dword_9040 = 1;
}

__int64 __fastcall sub_1A10(unsigned int *a1, _QWORD *a2)
{
  __int64 result; // rax

  result = (int)_byteswap_ulong(*a1);
  *a2 = result;
  return result;
}

__int64 __fastcall sub_1480(_QWORD *a1, __int64 *a2, __int64 *a3)
{
  __int64 v3; // rax
  _QWORD *v4; // r8
  __int64 v5; // r10
  __int64 v6; // rax
  __int64 v7; // rcx
  __int64 result; // rax

  v3 = *a2;
  v4 = a1;
  v5 = *a3;
  do
  {
    v6 = *v4++ ^ v3;
    v7 = v6;
    v3 = v5 ^ (a1[(unsigned __int8)v6 + 786] + (a1[BYTE1(v6) + 530] ^ (a1[BYTE3(v6) + 18] + a1[BYTE2(v6) + 274])));
    v5 = v7;
  }
  while ( v4 != a1 + 16 );
  result = a1[16] ^ v3;
  *a2 = a1[17] ^ v7;
  *a3 = result;
  return result;
}

__int64 __fastcall sub_1A40(_BYTE *a1, __int64 *a2)
{
  __int64 result; // rax

  result = *a2;
  a1[3] = *a2;
  *a1 = BYTE3(result);
  a1[1] = BYTE2(result);
  a1[2] = BYTE1(result);
  return result;
}

__int64 __fastcall sub_A80(__int64 a1, _BYTE *a2, unsigned __int16 a3)
{
  char v3; // r15
  unsigned __int16 v5; // di
  __int64 v6; // r13
  __int64 v7; // r14
  __int64 v8; // rbx
  char *v9; // rax
  char v10; // si
  __int16 v11; // r15
  __int16 v12; // ax
  __int16 v13; // r15
  __int64 result; // rax
  __int64 v15; // [rsp+0h] [rbp-68h]
  __int64 v17; // [rsp+10h] [rbp-58h] BYREF
  __int64 v18; // [rsp+18h] [rbp-50h] BYREF
  char v19[4]; // [rsp+20h] [rbp-48h] BYREF
  int v20; // [rsp+24h] [rbp-44h] BYREF
  unsigned __int64 v21; // [rsp+28h] [rbp-40h]

  v3 = a3;
  v5 = a3;
  v21 = __readfsqword(0x28u);
  if ( !dword_9040 )
    dword_9040 = 1;
  if ( a3 <= 7u )
  {
    v15 = a1;
    v6 = 84281096LL;
    v7 = 16909060LL;
  }
  else
  {
    v6 = 84281096LL;
    v7 = 16909060LL;
    v15 = a1 + 8LL * ((unsigned __int16)(a3 - 8) >> 3) + 8;
    do
    {
      sub_1A10(a1, &v17);
      sub_1A10(a1 + 4, &v18);
      a1 += 8LL;
      v17 ^= v7;
      v18 ^= v6;
      sub_1480(&dword_2A00, &v17, &v18);
      v7 = v17;
      v6 = v18;
    }
    while ( v15 != a1 );
    v5 = v3 & 7;
  }
  if ( v5 )
  {
    v8 = 0LL;
    v9 = (char *)v15;
    do
    {
      v10 = *v9++;
      v11 = (_WORD)v9 - v15;
      v19[v8] = v10;
      v8 = (__int16)((_WORD)v9 - v15);
    }
    while ( (__int16)((_WORD)v9 - v15) < (int)v5 );
    if ( v11 <= 7 )
    {
      v19[v11] = -1;
      if ( (__int16)(v11 + 1) <= 7 )
      {
        v19[(__int16)(v11 + 1)] = -1;
        if ( v11 != 6 )
        {
          v19[(__int16)(v11 + 2)] = -1;
          if ( v11 != 5 )
          {
            v19[(__int16)(v11 + 3)] = -1;
            if ( v11 != 4 )
            {
              v19[(__int16)(v11 + 4)] = -1;
              if ( v11 != 3 )
              {
                v19[(__int16)(v11 + 5)] = -1;
                if ( v11 != 2 )
                {
                  v19[(__int16)(v11 + 6)] = -1;
                  v12 = v11 + 7;
                  if ( v11 != 1 )
                  {
                    v13 = v11 + 8;
                    v19[v12] = -1;
                    if ( v13 != 8 )
                      v19[v13] = -1;
                  }
                }
              }
            }
          }
        }
      }
    }
    sub_1A10(v19, &v17);
    sub_1A10(&v20, &v18);
    v17 ^= v7;
    v18 ^= v6;
    sub_1480(&dword_2A00, &v17, &v18);
  }
  sub_1A40(a2, &v17);
  sub_1A40(a2 + 4, &v18);
  result = __readfsqword(0x28u) ^ v21;
  if ( result )
    return LsSecInit(a2 + 4, (__int64)&v18);
  return result;
}

__int64 __fastcall LsSecInit(_BYTE *a1, __int64 a2)
{
  _OWORD *v2; // rax

  v2 = a1;
  do
    *v2++ = 0LL;
  while ( v2 != (_OWORD *)(a1 + 8400) );
  a1[8400] = 0;
  a1[8401] = 0;
  a1[8402] = 0;
  a1[8403] = 0;
  a1[8404] = 0;
  a1[8405] = 0;
  a1[8406] = 0;
  a1[8407] = 0;
  if ( a2 )
    srand(a2);
  sub_A50(0.0);
  *((_DWORD *)a1 + 2100) = 1;
  return 0LL;
}

void __fastcall sub_1A80(unsigned __int64 a1, unsigned __int64 a2, __int16 a3)
{
  __int64 v3; // r8
  int v4; // r9d
  unsigned __int16 v5; // cx
  unsigned __int16 v6; // ax
  _BYTE *v7; // rdi
  _BYTE *v8; // rsi
  __int16 v9; // ax
  __int64 v10; // rax

  if ( a3 > 0 )
  {
    if ( (a1 >= a2 + 16 || a2 >= a1 + 16) && (unsigned __int16)a3 > 0xFu )
    {
      v3 = 0LL;
      v4 = 0;
      v5 = ((unsigned __int16)(a3 - 16) >> 4) + 1;
      v6 = 16 * v5;
      do
      {
        ++v4;
        *(__m128i *)(a1 + v3) = _mm_loadu_si128((const __m128i *)(a2 + v3));
        v3 += 16LL;
      }
      while ( v5 > (unsigned __int16)v4 );
      v7 = (_BYTE *)(v6 + a1);
      v8 = (_BYTE *)(v6 + a2);
      if ( a3 != v6 )
      {
        *v7 = *v8;
        if ( a3 > (__int16)(v6 + 1) )
        {
          v7[1] = v8[1];
          if ( a3 > (__int16)(v6 + 2) )
          {
            v7[2] = v8[2];
            if ( a3 > (__int16)(v6 + 3) )
            {
              v7[3] = v8[3];
              if ( a3 > (__int16)(v6 + 4) )
              {
                v7[4] = v8[4];
                if ( a3 > (__int16)(v6 + 5) )
                {
                  v7[5] = v8[5];
                  if ( a3 > (__int16)(v6 + 6) )
                  {
                    v7[6] = v8[6];
                    if ( a3 > (__int16)(v6 + 7) )
                    {
                      v9 = v6 + 8;
                      v7[7] = v8[7];
                      if ( a3 > v9 )
                      {
                        v7[8] = v8[8];
                        if ( a3 > (__int16)(v9 + 1) )
                        {
                          v7[9] = v8[9];
                          if ( a3 > (__int16)(v9 + 2) )
                          {
                            v7[10] = v8[10];
                            if ( a3 > (__int16)(v9 + 3) )
                            {
                              v7[11] = v8[11];
                              if ( a3 > (__int16)(v9 + 4) )
                              {
                                v7[12] = v8[12];
                                if ( a3 > (__int16)(v9 + 5) )
                                {
                                  v7[13] = v8[13];
                                  if ( a3 > (__int16)(v9 + 6) )
                                    v7[14] = v8[14];
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      v10 = 0LL;
      do
      {
        *(_BYTE *)(a1 + v10) = *(_BYTE *)(a2 + v10);
        ++v10;
      }
      while ( a3 > (__int16)v10 );
    }
  }
}

__int64 __fastcall LsSec1stStage(__int64 a1, __int64 a2)
{
  __int64 result; // rax
  __int64 v3[4]; // [rsp+8h] [rbp-20h] BYREF

  result = 4294967193LL;
  v3[0] = 0LL;
  if ( *(_DWORD *)(a1 + 8400) == 1 )
  {
    v3[0] = rand();
    sub_1A40(a2, v3);
    v3[0] = rand();
    sub_1A40(a2 + 4, v3);
    *(_DWORD *)(a1 + 8400) = 3;
    return 0LL;
  }
  return result;
}

__int64 __fastcall LsSec2ndStage(__int64 a1, __int64 a2, _BYTE *a3, __int64 a4)
{
  __int64 result; // rax
  __int64 v7[6]; // [rsp+8h] [rbp-30h] BYREF

  result = 4294967193LL;
  v7[0] = 0LL;
  if ( *(_DWORD *)(a1 + 8400) == 1 )
  {
    v7[0] = rand();
    sub_1A40(a3, v7);
    v7[0] = rand();
    sub_1A40(a3 + 4, v7);
    v7[0] = rand() & 7;
    sub_1A80(a1 + 24, (char *)&byte_4AC0 + 8 * v7[0], 8LL);
    sub_1A80(a1 + 32, a3, 8LL);
    sub_1A80(a1 + 40, a2, 8LL);
    sub_1A80(a1, a3, 4LL);
    sub_1A80(a1 + 4, a2, 4LL);
    *(_BYTE *)a1 = v7[0];
    sub_A80(a1 + 24, a4, 24LL);
    *(_DWORD *)(a1 + 8400) = 2;
    return 0LL;
  }
  return result;
}
