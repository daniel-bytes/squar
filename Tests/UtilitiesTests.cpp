#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Source/Utilities.h"

namespace squarunittests
{		
	TEST_CLASS(UtilitiesTests)
	{
	public:
		
		TEST_METHOD(Clip_Test)
		{
			float value;

			value = clip(.5f, 0.f, 1.f);
			Assert::AreEqual(.5f, value, 0.f);
			
			value = clip(.5f, 1.f, 2.f);
			Assert::AreEqual(1.f, value, 0.f);
			
			value = clip(.5f, 0.f, .4f);
			Assert::AreEqual(.4f, value, 0.f);
		}
		
		TEST_METHOD(Scale_Test)
		{
			float value;

			value = scale(.25f, 0.f, 100.f);
			Assert::AreEqual(25.f, value, 0.f);

			value = scale(.25f, 20.f, 100.f);
			Assert::AreEqual(40.f, value, 0.f);

			value = scale(.25f, -20.f, -100.f);
			Assert::AreEqual(-40.f, value, 0.f);

			value = scale(.25f, 100.f, 20.f);
			Assert::AreEqual(80.f, value, 0.f);
		}
	};
}