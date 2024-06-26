#pragma once

#include <TableFunctions/ITableFunction.h>

namespace DB
{
/* values(structure, values...) - creates a temporary storage filling columns with values
 * values is case-insensitive table function
 */
class TableFunctionValues : public ITableFunction
{
public:
    static constexpr auto name = "values";
    std::string getName() const override { return name; }
    bool hasStaticStructure() const override { return true; }
private:
    StoragePtr executeImpl(const ASTPtr & ast_function, ContextPtr context, const std::string & table_name, ColumnsDescription cached_columns) const override;
    const char * getStorageTypeName() const override { return "Values"; }

    ColumnsDescription getActualTableStructure(ContextPtr context) const override;
    void parseArguments(const ASTPtr & ast_function, ContextPtr context) override;

    static DataTypes getTypesFromArgument(const ASTPtr & arg, ContextPtr context);

    ColumnsDescription structure;
    bool has_structure_in_arguments;
};


}
