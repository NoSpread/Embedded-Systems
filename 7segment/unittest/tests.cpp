#include "catch.hpp"
#include "../7segment/include/7Segment.h"

TEST_CASE("Test Single Digit")
{
	SECTION("Digit 0")
	{
		const char result[] = " - \n| |\n   \n| |\n - \n";
		constexpr MultiDigit md{0};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 1")
	{
		const char result[] = "   \n  |\n   \n  |\n   \n";
		constexpr MultiDigit md{1};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 2")
	{
		const char result[] = " - \n  |\n - \n|  \n - \n";
		constexpr MultiDigit md{2};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 3")
	{
		const char result[] = " - \n  |\n - \n  |\n - \n";
		constexpr MultiDigit md{3};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 4")
	{
		const char result[] = "   \n| |\n - \n  |\n   \n";
		constexpr MultiDigit md{4};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 5")
	{
		const char result[] = " - \n|  \n - \n  |\n - \n";
		constexpr MultiDigit md{5};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 6")
	{
		const char result[] = " - \n|  \n - \n| |\n - \n";
		constexpr MultiDigit md{6};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 7")
	{
		const char result[] = " - \n  |\n   \n  |\n   \n";
		constexpr MultiDigit md{7};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 8")
	{
		const char result[] = " - \n| |\n - \n| |\n - \n";
		constexpr MultiDigit md{8};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}

	SECTION("Digit 9")
	{
		const char result[] = " - \n| |\n - \n  |\n - \n";
		constexpr MultiDigit md{9};
		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}
}

TEST_CASE("Multiple Digits")
{
	SECTION("all possible digits concatenated")
	{
		constexpr MultiDigit md{5, 4, 6, 3, 7, 2, 8, 1, 9, 0};
		const char result[] =
			" -       -   -   -   -   -       -   - \n|   | | |     |   |   | | |   | | | | |\n -   -   -   -       -   -       -     \n  |   | | |   |   | |   | |   |   | | |\n -       -   -       -   -       -   - \n";

		REQUIRE_THAT(static_cast<const char*>(md), Catch::Matchers::Equals(result));
	}
}
