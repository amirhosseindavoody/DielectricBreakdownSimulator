cc_library(
    name = "constants",
    hdrs = ["constants.h"],
    deps = [
    ],
)

cc_library(
    name = "node",
    srcs = ["node.cc"],
    hdrs = ["node.h"],
    deps = [":constants"],
)

cc_library(
    name = "node_manager",
    srcs = ["node_manager.cc"],
    hdrs = ["node_manager.h"],
    deps = [
        ":constants",
        ":node",
        ":random_position_generator",
    ],
)

cc_library(
    name = "random_position_generator",
    srcs = ["random_position_generator.cc"],
    hdrs = ["random_position_generator.h"],
    deps = [
        ":constants",
        ":node",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/hash",
    ],
)

cc_library(
    name = "breakdown_simulator",
    srcs = ["breakdown_simulator.cc"],
    hdrs = ["breakdown_simulator.h"],
    deps = [
        ":constants",
        ":node",
        ":random_position_generator",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":breakdown_simulator",
        ":constants",
        ":node",
        ":random_position_generator",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/time",
    ],
)
