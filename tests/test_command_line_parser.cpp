#include <gtest/gtest.h>

#include "command_line_parser.h"

#include <initializer_list>
#include <vector>

namespace {

ModuleArgs parse(std::initializer_list<const char*> arguments)
{
    std::vector<char*> argv;
    argv.reserve(arguments.size());
    for (const char* argument : arguments) {
        argv.push_back(const_cast<char*>(argument));
    }
    return parseCommandLineArgs(static_cast<int>(argv.size()), argv.data());
}

} // namespace

TEST(CommandLineParser, HelpIsSuccessfulExit)
{
    const ModuleArgs result = parse({"logos_host_qt", "--help"});

    EXPECT_FALSE(result.valid);
    EXPECT_TRUE(result.shouldExit);
    EXPECT_EQ(result.exitCode, 0);
}

TEST(CommandLineParser, VersionIsSuccessfulExit)
{
    const ModuleArgs result = parse({"logos_host_qt", "--version"});

    EXPECT_FALSE(result.valid);
    EXPECT_TRUE(result.shouldExit);
    EXPECT_EQ(result.exitCode, 0);
}

TEST(CommandLineParser, MalformedArgumentsRemainFailure)
{
    const ModuleArgs result = parse({"logos_host_qt", "--unknown"});

    EXPECT_FALSE(result.valid);
    EXPECT_TRUE(result.shouldExit);
    EXPECT_NE(result.exitCode, 0);
}

TEST(CommandLineParser, CompleteArgumentsStartHost)
{
    const ModuleArgs result = parse({
        "logos_host_qt",
        "--name",
        "storage_module",
        "--path",
        "/tmp/storage_module.so",
    });

    EXPECT_TRUE(result.valid);
    EXPECT_FALSE(result.shouldExit);
    EXPECT_EQ(result.exitCode, 0);
}
