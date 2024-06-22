#include "gcc-plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "tree-pass.h"
#include "context.h"
#include "dumpfile.h"

int plugin_is_GPL_compatible;

namespace {

const pass_data test_dump_pass_data = {
    GIMPLE_PASS, /* type */
    "test_dump", /* name */
    OPTGROUP_NONE, /* optinfo_flags */
    TV_NONE, /* tv_id */
    PROP_gimple_any, /* properties_required */
    0, /* properties_provided */
    0, /* properties_destroyed */
    0, /* todo_flags_start */
    0, /* todo_flags_finish */
};

class test_dump_pass : public gimple_opt_pass {
public:
    test_dump_pass(gcc::context *ctxt)
        : gimple_opt_pass(test_dump_pass_data, ctxt) {}

    unsigned int execute(function *fun) override {
        /* Diagnostic output: dumping the function name */
        fprintf(stderr, "Running test dump pass on function: %s\n", function_name(fun));
        if (dump_file) {
            fprintf(dump_file, "Running test dump pass on function: %s\n", function_name(fun));
        }
        return 0;
    }
};

} // namespace

int plugin_init(struct plugin_name_args *plugin_info,
                struct plugin_gcc_version *version) {
    if (!plugin_default_version_check(version, &gcc_version)) {
        return 1;
    }
    struct register_pass_info pass_info;
    pass_info.pass = new test_dump_pass(g);
    pass_info.reference_pass_name = "ssa";
    pass_info.ref_pass_instance_number = 1;
    pass_info.pos_op = PASS_POS_INSERT_AFTER;
    register_callback(plugin_info->base_name, PLUGIN_PASS_MANAGER_SETUP, nullptr, &pass_info);
    return 0;
}
