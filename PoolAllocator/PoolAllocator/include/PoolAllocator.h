#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#define CREATE( varName , blockCount , blockSize ) PoolAllocator<blockCount, blockSize> varName

class IHeap
{
public:

	virtual void* Allocate(size_t sizeInBytes) = 0;
	virtual void Deallocate(void*) = 0;
	virtual size_t Available() const = 0;
};


template <size_t bCount, size_t bSize >
class PoolAllocator : IHeap
{
public:
	auto Allocate(size_t sizeInBytes) -> void* override
	{
		if (sizeInBytes == 0 || sizeInBytes > bSize) return nullptr;

		for (size_t i = 0; i < bCount; i++)
		{
			if (blockUsed[i]) continue;
			blockUsed[i] = true;
			--freeBlocks;
			return &data[i];
		}

		return nullptr;
	}

	auto Deallocate(void* dealloc) -> void override
	{
		//                                                                      if pointer is not the start of the array
		if (dealloc == nullptr || dealloc > data[bCount - 1] || dealloc < data[0] || (static_cast<size_t*>(dealloc) - data[0]) % bSize != 0)
			return;

		size_t index = (static_cast<size_t*>(dealloc) - data[0]) / bSize;

		for (size_t i = 0; i < bSize; ++i)
		{
			data[index][i] = 0;
		}
		blockUsed[index] = false;
		++freeBlocks;
	}

	auto Available() const -> size_t override
	{
		return freeBlocks * bSize;
	}

private:
	size_t data[bCount][bSize] = {};
	bool blockUsed[bCount] = {};
	size_t freeBlocks{bCount};
};

#endif
