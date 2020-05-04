#include "catch.hpp"
#include "../String/include/Printf.h"
#include "../String/include/PreAllocString.h"

TEST_CASE("Testing Printf functions", "[TESTING]")
{
	SECTION("Testing Printf")
	{
		char dst[400];
		char* res = Printf(dst, &dst[399], "TEST");
		REQUIRE_THAT(res, Catch::Matchers::Equals("TEST"));
	}

	SECTION("Testing Printf format")
	{
		PreAllocString<300> AllocString;
		const char* expectedString =
			"0d:0 12d:12 0u:0 13u:13 -13d:-13 Qc:Q test123s:test123 0x:0x0 37x:0x25 -208957203x:0xf38b90ed 0b:0b0 235234b:0b111001011011100010 -3489753b:0b11111111110010101100000000100111 prozent:%";
		AllocString.AddFormat(
			"0d:%d 12d:%d 0u:%u 13u:%u -13d:%d Qc:%c test123s:%s 0x:%x 37x:%x -208957203x:%x 0b:%b 235234b:%b -3489753b:%b prozent:%%",
			0, 12, 0, 13, -13, 'Q', "test123", 0, 37, -208957203, 0, 235234, -3489753);
		REQUIRE_THAT(static_cast<const char*>(AllocString), Catch::Matchers::Equals(expectedString));
	}
}

TEST_CASE("Test implemented Operators")
{
	SECTION("testing =operator with char")
	{
		PreAllocString<11> AllocString;
		char myChar = 'a';
		AllocString = myChar;

		REQUIRE(AllocString[0] == 'a');
		REQUIRE(AllocString[1] == '\0');
	}

	SECTION("testing =operator with const char*")
	{
		PreAllocString<11> AllocString;
		const char* myConstCharPointer = "TEST";
		AllocString = myConstCharPointer;

		REQUIRE(AllocString[0] == 'T');
		REQUIRE(AllocString[1] == 'E');
		REQUIRE(AllocString[2] == 'S');
		REQUIRE(AllocString[3] == 'T');
		REQUIRE(AllocString[4] == '\0');
	}

	SECTION("testing += operator with char")
	{
		PreAllocString<11> AllocString;
		AllocString = 't';
		AllocString += 'e';
		AllocString += 's';
		AllocString += 't';

		REQUIRE(AllocString[0] == 't');
		REQUIRE(AllocString[1] == 'e');
		REQUIRE(AllocString[2] == 's');
		REQUIRE(AllocString[3] == 't');
		REQUIRE(AllocString[4] == '\0');
	}

	SECTION("testing += operator with const char*")
	{
		PreAllocString<11> AllocString;
		const char* testString = "testString";
		AllocString += testString;

		REQUIRE_THAT(static_cast<const char*>(AllocString), Catch::Matchers::Equals(testString));
	}
}

TEST_CASE("Testing member functions")
{
	SECTION("Testing GetLength")
	{
		PreAllocString<11> AllocString;
		AllocString = 't';
		AllocString += 'e';
		AllocString += 's';
		AllocString += 't';

		REQUIRE(AllocString.GetLength() == 4);
	}

	SECTION("Testing SizeOf")
	{
		PreAllocString<11> AllocString;

		REQUIRE(AllocString.SizeOf() == 11);
	}

	SECTION("Testing Empty")
	{
		PreAllocString<11> AllocString;
		AllocString += 'a';

		REQUIRE(AllocString[0] == 'a');

		AllocString.Empty();

		REQUIRE(AllocString[0] == '\0');
		REQUIRE(AllocString.GetLength() == 0);
	}

	SECTION("Testing Add Whitespace")
	{
		PreAllocString<11> AllocString;
		AllocString = 't';
		AllocString += 'e';
		AllocString += 's';
		AllocString.AddWhiteSpace();
		AllocString += 't';


		REQUIRE(AllocString[0] == 't');
		REQUIRE(AllocString[1] == 'e');
		REQUIRE(AllocString[2] == 's');
		REQUIRE(AllocString[3] == ' ');
		REQUIRE(AllocString[4] == 't');
		REQUIRE(AllocString[5] == '\0');
	}
}

TEST_CASE("Class Respects boundaries of string")
{
	SECTION("Using += char")
	{
		PreAllocString<3> AllocString;
		AllocString += 'e';
		AllocString += 'e';
		AllocString += 'e';

		REQUIRE(AllocString[2] == '\0');
	}

	SECTION("Using += string")
	{
		PreAllocString<10> AllocString;
		AllocString += "1234567890";

		REQUIRE_THAT(static_cast<const char*>(AllocString), Catch::Matchers::Equals("123456789"));
	}

	SECTION("Using = string")
	{
		PreAllocString<10> AllocString;
		AllocString = "1234567890";

		REQUIRE_THAT(static_cast<const char*>(AllocString), Catch::Matchers::Equals("123456789"));
	}

	SECTION("Using = string")
	{
		PreAllocString<10> AllocString;
		AllocString.AddFormat("%s", "1234567890");
		REQUIRE_THAT(static_cast<const char*>(AllocString), Catch::Matchers::Equals("123456789"));
	}
}
