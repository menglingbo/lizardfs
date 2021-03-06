/*
   Copyright 2013-2014 EditShare, 2013-2015 Skytechnology sp. z o.o.

   This file is part of LizardFS.

   LizardFS is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 3.

   LizardFS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with LizardFS. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "common/platform.h"

#include "common/chunk_part_type.h"
#include "common/exception.h"
#include "common/mfserr.h"
#include "common/network_address.h"

LIZARDFS_CREATE_EXCEPTION_CLASS(ConfigurationException, Exception);
LIZARDFS_CREATE_EXCEPTION_CLASS(FilesystemException, Exception);
LIZARDFS_CREATE_EXCEPTION_CLASS(InitializeException, Exception);
LIZARDFS_CREATE_EXCEPTION_CLASS(ConnectionException, Exception);
LIZARDFS_CREATE_EXCEPTION_CLASS(ReadException, Exception);
LIZARDFS_CREATE_EXCEPTION_CLASS(RecoverableReadException, ReadException);
LIZARDFS_CREATE_EXCEPTION_CLASS(UnrecoverableReadException, ReadException);
LIZARDFS_CREATE_EXCEPTION_CLASS(NoValidCopiesReadException, RecoverableReadException);

class ChunkCrcException : public RecoverableReadException {
public:
	ChunkCrcException(const std::string& message, const NetworkAddress& server,
			const ChunkPartType& chunkType)
			: RecoverableReadException(message + " (server " + server.toString() + ")"),
			  server_(server), chunkType_(chunkType) {
	}

	~ChunkCrcException() throw() {}
	const NetworkAddress& server() const throw() { return server_; }
	const ChunkPartType& chunkType() const throw() { return chunkType_; }

private:
	NetworkAddress server_;
	ChunkPartType chunkType_;
};

class ParseException : public Exception {
public:
	ParseException(const std::string& message)
			: Exception(message) {
	}

	ParseException(int line, const std::string& message)
			: Exception("line " + std::to_string(line) + " : " + message) {
	}

	~ParseException() throw() {}
};
