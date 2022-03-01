workspace(name = "birdcam")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

# Buildifier is written in Go and hence needs rules_go to be built.
# See https://github.com/bazelbuild/rules_go for the up to date setup instructions.
http_archive(
    name = "io_bazel_rules_go",
    sha256 = "d6b2513456fe2229811da7eb67a444be7785f5323c6708b38d851d2b51e54d83",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_go/releases/download/v0.30.0/rules_go-v0.30.0.zip",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.30.0/rules_go-v0.30.0.zip",
    ],
)

load("@io_bazel_rules_go//go:deps.bzl", "go_rules_dependencies")

go_rules_dependencies()

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains")

go_register_toolchains(version = "1.17.7")

http_archive(
    name = "bazel_gazelle",
    sha256 = "de69a09dc70417580aabf20a28619bb3ef60d038470c7cf8442fafcf627c21cb",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.24.0/bazel-gazelle-v0.24.0.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.24.0/bazel-gazelle-v0.24.0.tar.gz",
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
    downloaded_file_path = "com.nikon.snapbridge.cmru-2.8.3.apk",
    sha256 = "c0a3ce59c029cfd5f932486f63a05ed5cdd36728ac5ceac6197e595cd635bc8d",
    urls = [
        "https://cloudflare-ipfs.com/ipfs/QmczKJCUZN54WEYxJcxtMnUniz4zzdgAizmoUCEiyupj1U",
        "https://gateway.pinata.cloud/ipfs/QmczKJCUZN54WEYxJcxtMnUniz4zzdgAizmoUCEiyupj1U",
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
