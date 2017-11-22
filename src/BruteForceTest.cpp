#include <iostream>
#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include "BruteForce.h"

using namespace CppUnit;


class BruteForceTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestBruteForce);
	CPPUNIT_TEST(TestdecryptSHA256);

  public :

    void testedObject();

  private :

    BruteForce _bruteForce;

  protected :

    void TestDecryptSHA256(void);


};


void testedObject()
{
  bruteForce = new BruteForce();
}

void BruteForceTest::TestDecryptSHA256(void)
{

  CPPUNIT_ASSERT();
}
