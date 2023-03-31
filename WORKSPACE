workspace(name = "birdcam")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

# Buildifier is written in Go and hence needs rules_go to be built.
# See https://github.com/bazelbuild/rules_go for the up to date setup instructions.
http_archive(
    name = "io_bazel_rules_go",
    sha256 = "6b65cb7917b4d1709f9410ffe00ecf3e160edf674b78c54a894471320862184f",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_go/releases/download/v0.39.0/rules_go-v0.39.0.zip",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.39.0/rules_go-v0.39.0.zip",
    ],
)

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")

go_rules_dependencies()

go_register_toolchains(version = "1.20.2")

http_archive(
    name = "bazel_gazelle",
    sha256 = "727f3e4edd96ea20c29e8c2ca9e8d2af724d8c7778e7923a854b2c80952bc405",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.30.0/bazel-gazelle-v0.30.0.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.30.0/bazel-gazelle-v0.30.0.tar.gz",
    ],
)

load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")

gazelle_dependencies()

load("//:deps.bzl", "go_dependencies")

# gazelle:repository_macro deps.bzl%go_dependencies
go_dependencies()

http_archive(
    name = "com_google_protobuf",
    sha256 = "3bd7828aa5af4b13b99c191e8b1e884ebfa9ad371b0ce264605d347f135d2568",
    strip_prefix = "protobuf-3.19.4",
    urls = [
        "https://github.com/protocolbuffers/protobuf/archive/v3.19.4.tar.gz",
    ],
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

http_archive(
    name = "com_github_bazelbuild_buildtools",
    sha256 = "7f43df3cca7bb4ea443b4159edd7a204c8d771890a69a50a190dc9543760ca21",
    strip_prefix = "buildtools-5.0.1",
    urls = [
        "https://github.com/bazelbuild/buildtools/archive/refs/tags/5.0.1.tar.gz",
    ],
)

http_archive(
    name = "com_google_googletest",
    sha256 = "b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5",
    strip_prefix = "googletest-release-1.11.0",
    urls = [
        "https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz",
    ],
)

http_archive(
    name = "jadx_bin",
    build_file = "//third_party:jadx_bin.bazel",
    sha256 = "861533d8dc1264a712db86b61ff9fe0630b3b2bb52bd21e7cef02e6467a4ab83",
    urls = [
        "https://github.com/skylot/jadx/releases/download/v1.3.3/jadx-1.3.3.zip",
    ],
)

http_file(
    name = "snapbridge",
    downloaded_file_path = "com.nikon.snapbridge.cmru-2.9.0.apk",
    sha256 = "0e7ff5755dba8f15980b19fba20a4d5c59d77113c84cda1ab792750ccc2f5d47",
    urls = [
        "http://localhost:8000/SnapBridge_v2.9.0.apk",
    ],
)

http_archive(
    name = "hexray_tools",
    build_file = "//third_party:hexray_tools.bazel",
    sha256 = "83a2884e1b0f0ff223e68bfd8a7555efdbd079d1002474db9c32b1b92cd37ece",
    strip_prefix = "hexrays_tools-1d4fc103c7f0f21798ff89c4c9a12598a2b49500",
    urls = [
        "https://github.com/nihilus/hexrays_tools/archive/1d4fc103c7f0f21798ff89c4c9a12598a2b49500.zip",
    ],
)

http_archive(
    name = "bazel_skylib",
    sha256 = "af87959afe497dc8dfd4c6cb66e1279cb98ccc84284619ebfec27d9c09a903de",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.2.0/bazel-skylib-1.2.0.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.0/bazel-skylib-1.2.0.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()
