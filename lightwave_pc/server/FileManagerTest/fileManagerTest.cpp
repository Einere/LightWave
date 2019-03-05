#include "stdafx.h"
#include "CppUnitTest.h"


#include "../RTK/FileManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace FileManagerTest
{		
	TEST_CLASS(FileManagerTest)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			FileManager manager;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test)
		{
			Assert::AreEqual(1, 2);
		}

	};
}