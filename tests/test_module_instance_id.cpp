#include "command_line_parser.h"
#include <logos_container/module_descriptor.h>
#include "module_instance_id.h"

#include <gtest/gtest.h>

TEST(ModuleInstanceIdTest, ExplicitIdTakesPrecedenceOverPersistencePath)
{
    EXPECT_EQ(LogosCore::resolveRuntimeInstanceId(
                  "zone_0101", "/var/logos/instances/legacy-zone"),
              "zone_0101");
}

TEST(ModuleInstanceIdTest, PersistencePathProvidesCompatibilityFallback)
{
    EXPECT_EQ(LogosCore::resolveRuntimeInstanceId(
                  "", "/var/logos/instances/zone_0101/"),
              "zone_0101");
}

TEST(ModuleInstanceIdTest, MissingIdentityKeepsLegacyDefaultInstance)
{
    EXPECT_TRUE(LogosCore::resolveRuntimeInstanceId("", "").empty());
}

TEST(ModuleInstanceIdTest, RuntimeAddressRejectsUnsafeInstanceId)
{
    const LogosCore::ModuleAddress address{"lez_indexer_module", "zone/0101"};
    EXPECT_FALSE(address.isValid());
}

TEST(CommandLineParserTest, ParsesExplicitRuntimeInstanceId)
{
    char program[] = "logos_host_qt";
    char nameFlag[] = "--name";
    char name[] = "lez_indexer_module";
    char pathFlag[] = "--path";
    char path[] = "/tmp/lez_indexer_module.so";
    char instanceFlag[] = "--instance-id";
    char instance[] = "zone_0101";
    char* argv[] = {program, nameFlag, name, pathFlag, path, instanceFlag, instance};

    ModuleArgs args = parseCommandLineArgs(7, argv);

    ASSERT_TRUE(args.valid);
    EXPECT_EQ(args.instanceId, "zone_0101");
}
