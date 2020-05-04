#include "catch.hpp"
#include "../include/OptParser.h"

TEST_CASE("Argument Parsing", "[parsing]") {
    CmdLineOptParser parser;

	SECTION("Correct input simulation, return true")
	{
        const char* arg0 = "programname";
        const char* arg1 = "-a";
        const char* arg2 = "-b";
        const char* arg3 = "-c=test";
        const char* arg4 = "-dbla";
        const char* arg5 = "-e";
        const char* arg6 = "ok123";
        char* args[] = {
            const_cast<char*>(arg0),
            const_cast<char*>(arg1),
            const_cast<char*>(arg2),
            const_cast<char*>(arg3),
            const_cast<char*>(arg4),
            const_cast<char*>(arg5),
            const_cast<char*>(arg6)
        };
        REQUIRE(parser.Parse(7, args) == true);
	}

    SECTION("Bad value parse simulation, return false") {
        const char* arg0 = "programname";
        const char* arg1 = "-a";
        const char* arg2 = "-b";
        const char* arg3 = "-c=test";
        const char* arg4 = "-dbla";
        const char* arg5 = "-";
        char* args[] = {
            const_cast<char*>(arg0),
            const_cast<char*>(arg1),
            const_cast<char*>(arg2),
            const_cast<char*>(arg3),
            const_cast<char*>(arg4),
            const_cast<char*>(arg5)
        };
        REQUIRE(parser.Parse(6, args) == false);
    }

    SECTION("Bad value parse simulation (double space arg), return false") {
        const char* arg0 = "programname";
        const char* arg1 = "-a";
        const char* arg01 = " ";
        const char* arg2 = "abc";
        const char* arg3 = "DDD";
        char* args[] = {
            const_cast<char*>(arg0),
            const_cast<char*>(arg1),
            const_cast<char*>(arg01),
            const_cast<char*>(arg2),
        	const_cast<char*>(arg3)
        };
        REQUIRE(parser.Parse(4, args) == false);
    }

    SECTION("Char not printable simulation, return false") {
        const char* arg0 = "programname";
        const char* arg1 = "-a";
        const char* arg2 = "-b\r";
        char* args[] = {
            const_cast<char*>(arg0),
            const_cast<char*>(arg1),
            const_cast<char*>(arg2)
        };
        REQUIRE(parser.Parse(3, args) == false);
    }


}