def _patched_so_impl(ctx):
    args = ctx.actions.args()
    args.add("-src", ctx.files.src[0])
    out = ctx.actions.declare_file("lib{}.so".format(ctx.attr.name))
    args.add("-dst", out)

    for key, val in ctx.attr.patch_str.items():
        args.add("-patch", "=".join((key, val)))
    for dep in ctx.attr.remove_deps:
        args.add("-rmdep", dep)

    ctx.actions.run(
        executable = ctx.executable._patch_so,
        arguments = [args],
        inputs = ctx.files.src,
        outputs = [out],
        mnemonic = "PATCH",
    )

    linker_input = cc_common.create_linker_input(
        owner = ctx.label,
        user_link_flags = [
            "-L{}".format(out.dirname),
            "-l{}".format(ctx.attr.name),
        ],
    )
    linking_context = cc_common.create_linking_context(
        linker_inputs = depset([linker_input]),
    )

    return [
        DefaultInfo(files = depset([out])),
        CcInfo(linking_context = linking_context),
    ]

patched_so = rule(
    implementation = _patched_so_impl,
    attrs = {
        "src": attr.label(
            doc = "Shared Object file (.so) to patch.",
            allow_single_file = [".so"],
            mandatory = True,
        ),
        "patch_str": attr.string_dict(
            doc = "Dict of string table items to patch.",
        ),
        "remove_deps": attr.string_list(
            doc = "List of dependencies (.so files) to remove.",
        ),
        "_patch_so": attr.label(
            default = "//cmd/patch_so",
            executable = True,
            cfg = "exec",
        ),
        "_cc_toolchain": attr.label(
            default = Label("@rules_cc//cc:current_cc_toolchain"),
        ),
    },
)
