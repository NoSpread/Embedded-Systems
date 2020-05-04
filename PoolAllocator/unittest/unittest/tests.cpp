#include "catch.hpp"
#include "../../PoolAllocator/include/PoolAllocator.h"

TEST_CASE("Testing PoolAllocation", "[TESTING]") {

	//ALLOC
    SECTION("size smaller than blocksize returns nullptr") {
        CREATE(allocator, 2, 4);

        REQUIRE(allocator.Allocate(5) == nullptr);
    }

    SECTION("only allocate blockCount amount of blocks with allocation") {
        CREATE(allocator, 2, 4);

        allocator.Allocate(4);
        allocator.Allocate(4);
        
        REQUIRE(allocator.Allocate(4) == nullptr);
    }

    SECTION("only allocate blockCount amount of blocks with mixed allocation and deallocation") {
        CREATE(allocator, 2, 4);

        auto* temp = allocator.Allocate(4);
        auto* _temp = allocator.Allocate(4);
    	
        REQUIRE(nullptr == allocator.Allocate(4));

    	
        allocator.Deallocate(temp);
        allocator.Deallocate(_temp);

        temp = allocator.Allocate(4);
        _temp = allocator.Allocate(4);
    	
        REQUIRE(nullptr == allocator.Allocate(4));

    }
	
    // DEALLOC
    SECTION("deallocate doesnt crash program") {
        CREATE(allocator, 2, 8);
        allocator.Deallocate(nullptr);
    }

    SECTION("deallocate doesnt clear data outside of its array") {
        CREATE(allocator, 2, 8);
        size_t test = 27;
    	
        allocator.Deallocate(&test);
        REQUIRE(27 == test);
    }

    SECTION("deallocate only works with pointers on block beginning") {
        CREATE(allocator, 2, 4);

        auto* testPtr1 = static_cast<char*>(allocator.Allocate(4));
        *testPtr1 = 'a';
    	
        allocator.Deallocate(testPtr1 - 1);
        REQUIRE('a' == *testPtr1);
    }

    SECTION("deallocate clears space after usage") {
        CREATE(allocator, 2, 4);

        auto* testPtr1 = static_cast<char*>(allocator.Allocate(4));
        *testPtr1 = 'a';
    	
        allocator.Deallocate(testPtr1);
        REQUIRE(*testPtr1 == 0);
    }

	//AVAILABLE

    SECTION("without allocations") {
        CREATE(allocator, 8, 23);

        // should not allocate
        allocator.Allocate(24);

        REQUIRE(allocator.Available() == (8 * 23));
    }

    SECTION("when fully allocated") {
        CREATE(allocator, 4, 23);

    	allocator.Allocate(23);
        allocator.Allocate(23);
        allocator.Allocate(23);
        allocator.Allocate(23);

        REQUIRE(allocator.Available() == 0);
    }

    SECTION("when partially allocated") {
        CREATE(allocator, 4, 23);
    	
        allocator.Allocate(20);
        allocator.Allocate(15);
        allocator.Allocate(10);

        // should not allocate
        allocator.Allocate(25);

        REQUIRE(allocator.Available() == 23);
    }
}
