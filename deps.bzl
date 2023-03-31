load("@bazel_gazelle//:deps.bzl", "go_repository")

def go_dependencies():
    go_repository(
        name = "com_github_bgould_http",
        importpath = "github.com/bgould/http",
        sum = "h1:cZGCJ3RgHTi06zzYuDDgRqP00ttLVGJCoyfSAI+RywE=",
        version = "v0.0.0-20190627042742-d268792bdee7",
    )
    go_repository(
        name = "com_github_burntsushi_toml",
        importpath = "github.com/BurntSushi/toml",
        sum = "h1:WXkYYl6Yr3qBf1K79EBnL4mak0OimBfB0XUf9Vl28OQ=",
        version = "v0.3.1",
    )
    go_repository(
        name = "com_github_cpuguy83_go_md2man_v2",
        importpath = "github.com/cpuguy83/go-md2man/v2",
        sum = "h1:U+s90UTSYgptZMwQh2aRr3LuazLJIa+Pg3Kc1ylSYVY=",
        version = "v2.0.0-20190314233015-f79a8a8ca69d",
    )
    go_repository(
        name = "com_github_davecgh_go_spew",
        importpath = "github.com/davecgh/go-spew",
        sum = "h1:vj9j/u1bqnvCEfJOwUhtlOARqs3+rkHYY13jYWTU97c=",
        version = "v1.1.1",
    )
    go_repository(
        name = "com_github_eclipse_paho_mqtt_golang",
        importpath = "github.com/eclipse/paho.mqtt.golang",
        sum = "h1:1F8mhG9+aO5/xpdtFkW4SxOJB67ukuDC3t2y2qayIX0=",
        version = "v1.2.0",
    )
    go_repository(
        name = "com_github_fatih_structs",
        importpath = "github.com/fatih/structs",
        sum = "h1:Q7juDM0QtcnhCpeyLGQKyg4TOIghuNXrkL32pHAUMxo=",
        version = "v1.1.0",
    )
    go_repository(
        name = "com_github_frankban_quicktest",
        importpath = "github.com/frankban/quicktest",
        sum = "h1:19ARM85nVi4xH7xPXuc5eM/udya5ieh7b/Sv+d844Tk=",
        version = "v1.10.2",
    )
    go_repository(
        name = "com_github_go_ble_ble",
        importpath = "github.com/go-ble/ble",
        sum = "h1:wCW6nm32DzgPEmKK8GPJj0D1ZRGrnUgfiGsXaJoClNc=",
        version = "v0.0.0-20230130210458-dd4b07d15402",
    )
    go_repository(
        name = "com_github_go_ole_go_ole",
        importpath = "github.com/go-ole/go-ole",
        sum = "h1:/Fpf6oFPoeFik9ty7siob0G6Ke8QvQEuVcuChpwXzpY=",
        version = "v1.2.6",
    )
    go_repository(
        name = "com_github_godbus_dbus_v5",
        importpath = "github.com/godbus/dbus/v5",
        sum = "h1:4KLkAxT3aOY8Li4FRJe/KvhoNFFxo0m6fNuFUO8QJUk=",
        version = "v5.1.0",
    )
    go_repository(
        name = "com_github_google_go_cmp",
        importpath = "github.com/google/go-cmp",
        sum = "h1:X2ev0eStA3AbceY54o37/0PQ/UWqKEiiO2dKL5OPaFM=",
        version = "v0.5.2",
    )
    go_repository(
        name = "com_github_google_uuid",
        importpath = "github.com/google/uuid",
        sum = "h1:Gkbcsh/GbpXz7lPftLA3P6TYMwjCLYm83jiFQZF/3gY=",
        version = "v1.1.1",
    )
    go_repository(
        name = "com_github_juullabs_oss_cbgo",
        importpath = "github.com/JuulLabs-OSS/cbgo",
        sum = "h1:A5JdglvFot1J9qYR0POZ4qInttpsVPN9lqatjaPp2ro=",
        version = "v0.0.1",
    )
    go_repository(
        name = "com_github_konsorten_go_windows_terminal_sequences",
        importpath = "github.com/konsorten/go-windows-terminal-sequences",
        sum = "h1:CE8S1cTafDpPvMhIxNJKvHsGVBgn1xWYf1NbHQhywc8=",
        version = "v1.0.3",
    )
    go_repository(
        name = "com_github_kr_pretty",
        importpath = "github.com/kr/pretty",
        sum = "h1:Fmg33tUaq4/8ym9TJN1x7sLJnHVwhP33CNkpYV/7rwI=",
        version = "v0.2.1",
    )
    go_repository(
        name = "com_github_kr_pty",
        importpath = "github.com/kr/pty",
        sum = "h1:VkoXIwSboBpnk99O/KFauAEILuNHv5DVFKZMBN/gUgw=",
        version = "v1.1.1",
    )
    go_repository(
        name = "com_github_kr_text",
        importpath = "github.com/kr/text",
        sum = "h1:45sCR5RtlFHMR4UwH9sdQ5TC8v0qDQCHnXt+kaKSTVE=",
        version = "v0.1.0",
    )
    go_repository(
        name = "com_github_mattn_go_colorable",
        importpath = "github.com/mattn/go-colorable",
        sum = "h1:fFA4WZxdEF4tXPZVKMLwD8oUnCTTo08duU7wxecdEvA=",
        version = "v0.1.13",
    )
    go_repository(
        name = "com_github_mattn_go_isatty",
        importpath = "github.com/mattn/go-isatty",
        sum = "h1:DOKFKCQ7FNG2L1rbrmstDN4QVRdS89Nkh85u68Uwp98=",
        version = "v0.0.18",
    )
    go_repository(
        name = "com_github_mgutz_ansi",
        importpath = "github.com/mgutz/ansi",
        sum = "h1:5PJl274Y63IEHC+7izoQE9x6ikvDFZS2mDVS3drnohI=",
        version = "v0.0.0-20200706080929-d51e80ef957d",
    )
    go_repository(
        name = "com_github_mgutz_logxi",
        importpath = "github.com/mgutz/logxi",
        sum = "h1:n8cgpHzJ5+EDyDri2s/GC7a9+qK3/YEGnBsd0uS/8PY=",
        version = "v0.0.0-20161027140823-aebf8a7d67ab",
    )
    go_repository(
        name = "com_github_muka_go_bluetooth",
        importpath = "github.com/muka/go-bluetooth",
        sum = "h1:BuVRHr4HHJbk1DHyWkArJ7E8J/VA8ncCr/VLnQFazBo=",
        version = "v0.0.0-20221213043340-85dc80edc4e1",
    )
    go_repository(
        name = "com_github_niemeyer_pretty",
        importpath = "github.com/niemeyer/pretty",
        sum = "h1:fD57ERR4JtEqsWbfPhv4DMiApHyliiK5xCTNVSPiaAs=",
        version = "v0.0.0-20200227124842-a10e7caefd8e",
    )
    go_repository(
        name = "com_github_paypal_gatt",
        importpath = "github.com/paypal/gatt",
        sum = "h1:RHRtrMle1AlWsMdCoIQIbq7IB2y8/5qEsUoAzjCCSCw=",
        version = "v0.0.0-20151011220935-4ae819d591cf",
    )
    go_repository(
        name = "com_github_pkg_errors",
        importpath = "github.com/pkg/errors",
        sum = "h1:FEBLx1zS214owpjy7qsBeixbURkuhQAwrK5UwLGTwt4=",
        version = "v0.9.1",
    )
    go_repository(
        name = "com_github_pmezard_go_difflib",
        importpath = "github.com/pmezard/go-difflib",
        sum = "h1:4DBwDE0NGyQoBHbLQYPwSUPoCMWR5BEzIk/f1lZbAQM=",
        version = "v1.0.0",
    )
    go_repository(
        name = "com_github_raff_goble",
        importpath = "github.com/raff/goble",
        sum = "h1:JtoVdxWJ3tgyqtnPq3r4hJ9aULcIDDnPXBWxZsdmqWU=",
        version = "v0.0.0-20190909174656-72afc67d6a99",
    )
    go_repository(
        name = "com_github_russross_blackfriday_v2",
        importpath = "github.com/russross/blackfriday/v2",
        sum = "h1:lPqVAte+HuHNfhJ/0LC98ESWRz8afy9tM/0RK8m9o+Q=",
        version = "v2.0.1",
    )
    go_repository(
        name = "com_github_shurcool_sanitized_anchor_name",
        importpath = "github.com/shurcooL/sanitized_anchor_name",
        sum = "h1:PdmoCO6wvbs+7yrJyMORt4/BmY5IYyJwS/kOiWx8mHo=",
        version = "v1.0.0",
    )
    go_repository(
        name = "com_github_sirupsen_logrus",
        importpath = "github.com/sirupsen/logrus",
        sum = "h1:trlNQbNUG3OdDrDil03MCb1H2o9nJ1x4/5LYw7byDE0=",
        version = "v1.9.0",
    )
    go_repository(
        name = "com_github_stretchr_objx",
        importpath = "github.com/stretchr/objx",
        sum = "h1:M2gUjqZET1qApGOWNSnZ49BAIMX4F/1plDv3+l31EJ4=",
        version = "v0.4.0",
    )
    go_repository(
        name = "com_github_stretchr_testify",
        importpath = "github.com/stretchr/testify",
        sum = "h1:s5PTfem8p8EbKQOctVV53k6jCJt3UX4IEJzwh+C324Q=",
        version = "v1.7.5",
    )
    go_repository(
        name = "com_github_suapapa_go_eddystone",
        importpath = "github.com/suapapa/go_eddystone",
        sum = "h1:mfW3eNoRPpaZ0iARRZtEyudFfNFtytqeCexwXg1wIKE=",
        version = "v1.3.1",
    )
    go_repository(
        name = "com_github_urfave_cli",
        importpath = "github.com/urfave/cli",
        sum = "h1:gsqYFH8bb9ekPA12kRo0hfjngWQjkJPlN9R0N78BoUo=",
        version = "v1.22.2",
    )
    go_repository(
        name = "com_github_valyala_fastjson",
        importpath = "github.com/valyala/fastjson",
        sum = "h1:tAKFnnwmeMGPbwJ7IwxcTPCNr3uIzoIj3/Fh90ra4xc=",
        version = "v1.6.3",
    )
    go_repository(
        name = "com_github_yuin_goldmark",
        importpath = "github.com/yuin/goldmark",
        sum = "h1:/vn0k+RBvwlxEmP5E7SZMqNxPhfMVFEJiykr15/0XKM=",
        version = "v1.4.1",
    )
    go_repository(
        name = "in_gopkg_check_v1",
        importpath = "gopkg.in/check.v1",
        sum = "h1:BLraFXnmrev5lT+xlilqcH8XK9/i0At2xKjWk4p6zsU=",
        version = "v1.0.0-20200227125254-8fa46927fb4f",
    )
    go_repository(
        name = "in_gopkg_yaml_v2",
        importpath = "gopkg.in/yaml.v2",
        sum = "h1:/eiJrUcujPVeJ3xlSWaiNi3uSVmDGBK1pDHUHAnao1I=",
        version = "v2.2.4",
    )
    go_repository(
        name = "in_gopkg_yaml_v3",
        importpath = "gopkg.in/yaml.v3",
        sum = "h1:fxVm/GzAzEWqLHuvctI91KS9hhNmmWOoWu0XTYJS7CA=",
        version = "v3.0.1",
    )
    go_repository(
        name = "org_golang_x_crypto",
        importpath = "golang.org/x/crypto",
        sum = "h1:7I4JAnoQBe7ZtJcBaYHi5UtiO8tQHbUSXxL+pnGRANg=",
        version = "v0.0.0-20210921155107-089bfa567519",
    )
    go_repository(
        name = "org_golang_x_mod",
        importpath = "golang.org/x/mod",
        sum = "h1:6zppjxzCulZykYSLyVDYbneBfbaBIQPYMevg0bEwv2s=",
        version = "v0.6.0-dev.0.20220419223038-86c51ed26bb4",
    )
    go_repository(
        name = "org_golang_x_net",
        importpath = "golang.org/x/net",
        sum = "h1:OfiFi4JbukWwe3lzw+xunroH1mnC1e2Gy5cxNJApiSY=",
        version = "v0.0.0-20211015210444-4f30a5c0130f",
    )
    go_repository(
        name = "org_golang_x_sync",
        importpath = "golang.org/x/sync",
        sum = "h1:5KslGYwFpkhGh+Q16bwMP3cOontH8FOep7tGV86Y7SQ=",
        version = "v0.0.0-20210220032951-036812b2e83c",
    )
    go_repository(
        name = "org_golang_x_sys",
        importpath = "golang.org/x/sys",
        sum = "h1:MVltZSvRTcU2ljQOhs94SXPftV6DCNnZViHeQps87pQ=",
        version = "v0.6.0",
    )
    go_repository(
        name = "org_golang_x_text",
        importpath = "golang.org/x/text",
        sum = "h1:olpwvP2KacW1ZWvsR7uQhoyTYvKAupfQrRGBFM352Gk=",
        version = "v0.3.7",
    )
    go_repository(
        name = "org_golang_x_tools",
        importpath = "golang.org/x/tools",
        sum = "h1:loJ25fNOEhSXfHrpoGj91eCUThwdNX6u24rO1xnNteY=",
        version = "v0.1.11",
    )
    go_repository(
        name = "org_golang_x_xerrors",
        importpath = "golang.org/x/xerrors",
        sum = "h1:go1bK/D/BFZV2I8cIQd1NKEZ+0owSTG1fDTci4IqFcE=",
        version = "v0.0.0-20200804184101-5ec99f83aff1",
    )
    go_repository(
        name = "org_tinygo_x_bluetooth",
        importpath = "tinygo.org/x/bluetooth",
        sum = "h1:5RTUh28WBtWfRtwFcsDcdiCvlSWr9F7fHxRikQZW/Io=",
        version = "v0.6.0",
    )
    go_repository(
        name = "org_tinygo_x_drivers",
        importpath = "tinygo.org/x/drivers",
        sum = "h1:fUy4OmLOWWYCOzDp/83Qewej1Q+YgUpwkm11e7gxUc0=",
        version = "v0.23.0",
    )
    go_repository(
        name = "org_tinygo_x_tinyfont",
        importpath = "tinygo.org/x/tinyfont",
        sum = "h1:HIRLQoI3oc+2CMhPcfv+Ig88EcTImE/5npjqOnMD4lM=",
        version = "v0.3.0",
    )
    go_repository(
        name = "org_tinygo_x_tinyterm",
        importpath = "tinygo.org/x/tinyterm",
        sum = "h1:80i+j+KWoxCFa/Xfp6pWbh79x+8zUdMXC1vaKj2QhkY=",
        version = "v0.1.0",
    )
    go_repository(
        name = "com_github_glerchundi_subcommands",
        importpath = "github.com/glerchundi/subcommands",
        sum = "h1:RlQI4RJwlknlSycN+MmXzq1O3k9ruRWRlYHfLgRy824=",
        version = "v0.0.0-20181212083838-923a6ccb11f8",
    )
    go_repository(
        name = "com_github_go_kit_log",
        importpath = "github.com/go-kit/log",
        sum = "h1:MRVx0/zhvdseW+Gza6N9rVzU/IVzaeE1SFI4raAhmBU=",
        version = "v0.2.1",
    )
    go_repository(
        name = "com_github_go_logfmt_logfmt",
        importpath = "github.com/go-logfmt/logfmt",
        sum = "h1:otpy5pqBCBZ1ng9RQ0dPu4PN7ba75Y/aA+UpowDyNVA=",
        version = "v0.5.1",
    )
    go_repository(
        name = "com_github_hajimehoshi_go_jisx0208",
        importpath = "github.com/hajimehoshi/go-jisx0208",
        sum = "h1:9gtYf7X5iKJla3QaBqgpqapg8xR/mhQ61+LMByaevP0=",
        version = "v1.0.0",
    )
    go_repository(
        name = "com_github_pelletier_go_toml",
        importpath = "github.com/pelletier/go-toml",
        sum = "h1:aetoXYr0Tv7xRU/V4B4IZJ2QcbtMUFoNb3ORp7TzIK4=",
        version = "v1.6.0",
    )
    go_repository(
        name = "com_github_peterbourgon_ff_v3",
        importpath = "github.com/peterbourgon/ff/v3",
        sum = "h1:0GNhbRhO9yHA4CC27ymskOsuRpmX0YQxwxM9UPiP6JM=",
        version = "v3.1.2",
    )
    go_repository(
        name = "com_github_sago35_go_bdf",
        importpath = "github.com/sago35/go-bdf",
        sum = "h1:MoPr+c4ADKs/Rqs5ffyc7dI8kxY4vL7nB0YgD/zAUXA=",
        version = "v0.0.0-20200313142241-6c17821c91c4",
    )
    go_repository(
        name = "com_github_saltosystems_winrt_go",
        importpath = "github.com/saltosystems/winrt-go",
        sum = "h1:sxsy5XkcxSzkiUkYgx38V9JviWLL8wthO2TURCi0Lcs=",
        version = "v0.0.0-20230124093143-967a889c6c8f",
    )
    go_repository(
        name = "com_github_tdakkota_win32metadata",
        importpath = "github.com/tdakkota/win32metadata",
        sum = "h1:0xoy5sPaOy8QDRc16hdvuFD4suyCVO2m37V8zdIk2kI=",
        version = "v0.1.0",
    )
    go_repository(
        name = "com_github_tinygo_org_cbgo",
        importpath = "github.com/tinygo-org/cbgo",
        sum = "h1:3D76CRYbH03Rudi8sEgs/YO0x3JIMdyq8jlQtk/44fU=",
        version = "v0.0.4",
    )
    go_repository(
        name = "org_golang_x_image",
        importpath = "golang.org/x/image",
        sum = "h1:RNPAfi2nHY7C2srAV8A49jpsYr0ADedCk1wq6fTMTvs=",
        version = "v0.0.0-20210628002857-a66eb6448b8d",
    )
    go_repository(
        name = "org_golang_x_term",
        importpath = "golang.org/x/term",
        sum = "h1:v+OssWQX+hTHEmOBgwxdZxK4zHq3yOs8F9J7mk0PY8E=",
        version = "v0.0.0-20201126162022-7de9c90e9dd1",
    )
    go_repository(
        name = "org_tinygo_x_tinyfs",
        importpath = "tinygo.org/x/tinyfs",
        sum = "h1:M0lwZC/dEGFt16XYN5GTQsif/qCkAN2qUVNxELVD1xg=",
        version = "v0.2.0",
    )
