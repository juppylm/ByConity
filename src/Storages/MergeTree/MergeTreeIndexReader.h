#pragma once

#include <Storages/MergeTree/MergeTreeReaderStream.h>
#include <Storages/MergeTree/MergeTreeIndices.h>
#include <Storages/MergeTree/MergeTreeData.h>
#include <Storages/MergeTree/IMergeTreeReaderStream.h>

namespace DB
{

class MergeTreeIndexReader
{
static constexpr char const * INDEX_FILE_EXTENSION = ".idx";
public:
    MergeTreeIndexReader(
        MergeTreeIndexPtr index_,
        MergeTreeData::DataPartPtr part_,
        size_t marks_count_,
        const MarkRanges & all_mark_ranges_,
        MergeTreeReaderSettings settings,
        MarkCache * mark_cache,
        const ProgressCallback & internal_progress_cb_ = {});

    void seek(size_t mark);

    MergeTreeIndexGranulePtr read();

private:
    MergeTreeIndexPtr index;
    std::unique_ptr<IMergeTreeReaderStream> stream;
};

}
