/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef _ZIP_ARCHIVE_H
#define _ZIP_ARCHIVE_H

#include "IArchiveFactory.h"
#include "BufferedArchive.h"
#include "minizip/unzip.h"

#include <string>
#include <vector>


/**
 * Creates zip compressed, single-file archives.
 * @see CZipArchive
 */
class CZipArchiveFactory : public IArchiveFactory {
public:
	CZipArchiveFactory(): IArchiveFactory("sdz") {}

private:
	IArchive* DoCreateArchive(const std::string& filePath) const;
};


/**
 * A zip compressed, single-file archive.
 */
class CZipArchive : public CBufferedArchive
{
public:
	CZipArchive(const std::string& archiveName);
	virtual ~CZipArchive();

	int GetType() const override { return ARCHIVE_TYPE_SDZ; }

	bool IsOpen() override;

	unsigned int NumFiles() const override;
	void FileInfo(unsigned int fid, std::string& name, int& size) const override;
	#if 0
	unsigned int GetCrc32(unsigned int fid);
	#endif

protected:
	unzFile zip;

	struct FileData {
		unz_file_pos fp;
		int size;
		std::string origName;
		unsigned int crc;
	};
	std::vector<FileData> fileData;

	bool GetFileImpl(unsigned int fid, std::vector<std::uint8_t>& buffer) override;
};

#endif // _ZIP_ARCHIVE_H
