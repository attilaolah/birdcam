def _version_script_impl(ctx):
    output = ctx.actions.declare_file("{}.lds".format(ctx.attr.name))
    ctx.actions.symlink(
        output = output,
        target_file = ctx.files.src[0],
    )

    return [
        DefaultInfo(files = depset([output])),
        CcInfo(),
    ]

version_script = rule(
    implementation = _version_script_impl,
    attrs = {
        "src": attr.label(
            doc = "Version Script file (.lds) to use as the source.",
            allow_single_file = [".lds"],
            mandatory = True,
        ),
    },
)
