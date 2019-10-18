#include "stdafx.h"
#pragma hdrstop


class MemPool {

public:
	MemPool(size_t blockSize, size_t blockNum) :
		_blockSize(blockSize),
		_blockNum(blockNum)
	{
		_pdataBeg = new uint8_t[_blockSize * _blockNum];
		_pdataCur = _pdataBeg;
	}


	size_t getTotalBlocks() const {
		return _blockNum;
	}

	size_t getAllocatedBlocks() const {
		return (_pdataCur - _pdataBeg) / _blockSize - _freeBlocks.size();
	}

	size_t getFreeBlocks() const {
		return getTotalBlocks() - getAllocatedBlocks();
	}

	uint8_t* allocateBlock() {
		uint8_t* newBlock = nullptr;

		if (getFreeBlocks() == 0)
			return newBlock;

		if (_freeBlocks.empty()) {
			newBlock = _pdataCur;
			_pdataCur += _blockSize;
		}
		else
		{
			newBlock = *_freeBlocks.begin();
			_freeBlocks.erase(newBlock);
		}
		return newBlock;
	}

	bool freeBlock(uint8_t* block) {

		if (getAllocatedBlocks() == 0 || 
			block < _pdataBeg || 
			block > _pdataBeg + (_blockNum - 1) * _blockSize ||
			(block - _pdataBeg) % _blockSize != 0)
			return false;
		
		if (_pdataCur - block == 1) {
			_pdataCur -= _blockSize;
			_freeBlocks.erase(_pdataCur);
		}
		else
			_freeBlocks.insert(block);

		return true;
	}

	void PrintStat() const {
		uint8_t* tdata = _pdataBeg;

		while (tdata < _pdataCur) {
			if (_freeBlocks.empty() || _freeBlocks.find(tdata) == _freeBlocks.end())
				cout << "\n   " << hex << (size_t)tdata << dec;
			tdata += _blockSize;
		}
	}

	~MemPool() {
		delete[] _pdataBeg;
	}

private:

	uint8_t* _pdataBeg;
	uint8_t* _pdataCur;

	size_t _blockSize;
	size_t _blockNum;
	unordered_set<uint8_t*> _freeBlocks;
};


void printPoolStat(const MemPool& mp) {
	cout << "\nAllocated blocks: " << mp.getAllocatedBlocks();
	cout << "\nFree blocks     : " << mp.getFreeBlocks();
	cout << "\nList of blocks  : ";
	mp.PrintStat();
}

void testMemPool() {

	MemPool mp(0x40, 5);
	cout << "\nTotal blocks: " << mp.getTotalBlocks() << "\n";
	printPoolStat(mp);

	uint8_t* b1 = mp.allocateBlock();
	printPoolStat(mp);
	uint8_t* b2 = mp.allocateBlock();
	printPoolStat(mp);
	uint8_t* b3 = mp.allocateBlock();
	printPoolStat(mp);

	mp.freeBlock(b1);
	printPoolStat(mp);
	mp.freeBlock(b3);
	printPoolStat(mp);

	uint8_t* b11 = mp.allocateBlock();
	printPoolStat(mp);
	uint8_t* b33 = mp.allocateBlock();
	printPoolStat(mp);
}

int main7(int argc, char* argv[])
{
	cout << "\n *** main-7 ***";
	testMemPool();
	return 0;
}
