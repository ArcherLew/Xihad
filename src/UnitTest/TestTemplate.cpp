#include "CppUnitTest.h"

// Assert::AreEqual(), ...
// Logger::WriteMessage()
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace xihad { namespace UnitTest 
{
	// TODO: �����޸�����
	TEST_CLASS(CurrentTestClass)
	{
	public:
		// This method will run before every TestMethod in current class.
		TEST_METHOD_INITIALIZE(initState)
		{
		}

		// TODO: �޸Ĳ��Է�����������鿴���
		TEST_METHOD(TestTemplateFunction)
		{
		}

		// This method will run after run every TestMethod in current class.
		TEST_METHOD_CLEANUP(cleanupState)
		{
		}
	};
}}

