#!/usr/bin/env bash

CURDIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
# shellcheck source=../shell_config.sh
. "$CURDIR"/../shell_config.sh

set -e

create_query="CREATE TABLE test.subcolumns(n Nullable(UInt32), a1 Array(UInt32),\
    a2 Array(Array(Array(UInt32))), a3 Array(Nullable(UInt32)), t Tuple(s String, v UInt32), m Map(String, UInt32) KV)"

declare -a ENGINES=("CnchMergeTree ORDER BY tuple()")

for engine in "${ENGINES[@]}"; do
    echo $engine
    $CLICKHOUSE_CLIENT --query "DROP TABLE IF EXISTS test.subcolumns"
    $CLICKHOUSE_CLIENT --query "$create_query ENGINE = $engine" --allow_experimental_map_type 1
    $CLICKHOUSE_CLIENT --query "INSERT INTO test.subcolumns VALUES (100, [1, 2, 3], [[[1, 2], [], [4]], [[5, 6], [7, 8]], [[]]], [1, NULL, 2], ('foo', 200), map('foo', 1, 'bar', 42))"
    $CLICKHOUSE_CLIENT --query "SELECT * FROM test.subcolumns"
    $CLICKHOUSE_CLIENT --query "SELECT n, n.null, a1, a1.size0, a2, a2.size0, a2.size1, a2.size2, a3, a3.size0, a3.null, t, t.s, t.v, m, m.key, m.value FROM test.subcolumns"
done

$CLICKHOUSE_CLIENT -q "DROP TABLE test.subcolumns"
