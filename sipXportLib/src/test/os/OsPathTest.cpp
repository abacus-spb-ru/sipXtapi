//
// Copyright (C) 2007-2010 SIPez LLC  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// Copyright (C) 2004-2006 SIPfoundry Inc.
// Licensed by SIPfoundry under the LGPL license.
//
// Copyright (C) 2004-2006 Pingtel Corp.  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// $$
///////////////////////////////////////////////////////////////////////////////

#include <os/OsFS.h>
#include <sipxunittests.h>
#include <os/OsTestUtilities.h>
#include <sipxunit/TestUtilities.h>

class OsPathTest : public SIPX_UNIT_BASE_CLASS
{
    CPPUNIT_TEST_SUITE(OsPathTest);
    CPPUNIT_TEST(testPathInfo);
    CPPUNIT_TEST_SUITE_END();

    /** where all tests should r/w data */
    OsPath mRootPath;

public:

    void setUp()
    {
        //OsTestUtilities::createTestDir(mRootPath);
    }


    void tearDown()
    {
        //OsTestUtilities::removeTestDir(mRootPath);
    }

    void testPathInfo()
    {
        UtlString testDir = "../../filename.ext";
        OsPath testPath = testDir;

        UtlString parentPath;
        parentPath.append("..").append(OsPath::separator).append("..").append(OsPath::separator);

        ASSERT_STR_EQUAL_MESSAGE("Extension", ".ext", testPath.getExt().data());
        ASSERT_STR_EQUAL_MESSAGE("Parent Path", parentPath, testPath.getDirName().data());
        ASSERT_STR_EQUAL_MESSAGE("Volume", "", testPath.getVolume().data());
        ASSERT_STR_EQUAL_MESSAGE("Filename no extension", "filename",
                                     testPath.getFilename().data());

        // little risky, may not have permissions, but '../../' is too
        // good a test to not try. Refactor if this is bad assumption
        OsFile file(testPath);
        file.touch();

        OsPath nativePath;
        testPath.getNativePath(nativePath);

        // dont' know what's right, but know whats wrong
        CPPUNIT_ASSERT_MESSAGE("Resolved relative path", !nativePath.contains(".."));
        //printf("Native path is %s\n", nativePath.data());

        file.remove();
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION(OsPathTest);