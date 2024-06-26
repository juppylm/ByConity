#pragma once

#include <common/shared_ptr_helper.h>
#include <Storages/System/IStorageSystemOneBlock.h>


namespace DB
{

class Context;


/// Implements the `mutations` system table, which provides information about the status of mutations
/// in the MergeTree tables.
class StorageSystemMutations final : public shared_ptr_helper<StorageSystemMutations>, public IStorageSystemOneBlock<StorageSystemMutations>
{
    friend struct shared_ptr_helper<StorageSystemMutations>;
public:
    String getName() const override { return "SystemMutations"; }

    static NamesAndTypesList getNamesAndTypes();

protected:
    using IStorageSystemOneBlock::IStorageSystemOneBlock;

    void fillData(MutableColumns & res_columns, ContextPtr context, const SelectQueryInfo & query_info) const override;

private:
    static void fillCnchData(MutableColumns & res_columns, ContextPtr context, const ASTPtr & query);
};

}
