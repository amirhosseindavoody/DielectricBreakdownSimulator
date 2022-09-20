cc_library(
    name = "constants",
    hdrs = ["constants.h"],
)

cc_library(
    name = "node",
    hdrs = ["node.h"],
    srcs = ["node.cc"],
    deps = [":constants"]
)

cc_library(
    name = "RandomPositionGenerator",
    hdrs = ["RandomPositionGenerator.h"],
    srcs = ["RandomPositionGenerator.cc"],
    deps = [
        ":constants",
        ":Node",
        "@com_google_absl//absl/hash",
        "@com_github_google_glog//:glog",
    ]
)

cc_library(
    name = "BreakdownSimulator",
    hdrs = ["BreakdownSimulator.h"],
    srcs = ["BreakdownSimulator.cc"],
    deps = [
        ":node",
        ":constants",
        ":RandomPositionGenerator",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/strings",
        "@com_github_google_glog//:glog",
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps=[
        ":node",
        ":constants",
        ":RandomPositionGenerator",
        ":BreakdownSimulator",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
)