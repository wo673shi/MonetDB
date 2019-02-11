/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with sql2h.py. Do not edit this file directly.
{ "21_dependency_views", "\n\nCREATE VIEW sys.ids (id, name, schema_id, table_id, table_name, obj_type, sys_table) AS\nSELECT id, name, cast(null as int) as schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'author' AS obj_type, 'sys.auths' AS sys_table FROM sys.auths UNION ALL\nSELECT id, name, cast(null as int) as schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'schema', 'sys.schemas' FROM sys.schemas UNION ALL\nSELECT id, name, schema_id, id as table_id, name as table_name, case when type = 1 then 'view' else 'table' end, 'sys._tables' FROM sys._tables UNION ALL\nSELECT id, name, schema_id, id as table_id, name as table_name, case when type = 1 then 'view' else 'table' end, 'tmp._tables' FROM tmp._tables UNION ALL\nSELECT c.id, c.name, t.schema_id, c.table_id, t.name as table_name, 'column', 'sys._columns' FROM sys._columns c JOIN sys._tables t ON c.table_id = t.id UNION ALL\nSELECT c.id, c.name, t.schema_id, c.table_id, t.name as table_name, 'column', 'tmp._columns' FROM tmp._columns c JOIN tmp._tables t ON c.table_id = t.id UNION ALL\nSELECT k.id, k.name, t.schema_id, k.table_id, t.name as table_name, 'key', 'sys.keys' FROM sys.keys k JOIN sys._tables t ON k.table_id = t.id UNION ALL\nSELECT k.id, k.name, t.schema_id, k.table_id, t.name as table_name, 'key', 'tmp.keys' FROM tmp.keys k JOIN tmp._tables t ON k.table_id = t.id UNION ALL\nSELECT i.id, i.name, t.schema_id, i.table_id, t.name as table_name, 'index', 'sys.idxs' FROM sys.idxs i JOIN sys._tables t ON i.table_id = t.id UNION ALL\nSELECT i.id, i.name, t.schema_id, i.table_id, t.name as table_name, 'index', 'tmp.idxs' FROM tmp.idxs i JOIN tmp._tables t ON i.table_id = t.id UNION ALL\nSELECT g.id, g.name, t.schema_id, g.table_id, t.name as table_name, 'trigger', 'sys.triggers' FROM sys.triggers g JOIN sys._tables t ON g.table_id = t.id UNION ALL\nSELECT g.id, g.name, t.schema_id, g.table_id, t.name as table_name, 'trigger', 'tmp.triggers' FROM tmp.triggers g JOIN tmp._tables t ON g.table_id = t.id UNION ALL\nSELECT id, name, schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, case when type = 2 then 'procedure' else 'function' end, 'sys.functions' FROM sys.functions UNION ALL\nSELECT a.id, a.name, f.schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, case when f.type = 2 then 'procedure arg' else 'function arg' end, 'sys.args' FROM sys.args a JOIN sys.functions f ON a.func_id = f.id UNION ALL\nSELECT id, name, schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'sequence', 'sys.sequences' FROM sys.sequences UNION ALL\nSELECT id, sqlname, schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'type', 'sys.types' FROM sys.types WHERE id > 2000 \nORDER BY id;\n\n\nGRANT SELECT ON sys.ids TO PUBLIC;\nCREATE TABLE sys.dependency_types (\ndependency_type_id SMALLINT NOT NULL PRIMARY KEY,\ndependency_type_name VARCHAR(15) NOT NULL UNIQUE);\nINSERT INTO sys.dependency_types (dependency_type_id, dependency_type_name) VALUES\n(1, 'SCHEMA'),\n(2, 'TABLE'),\n(3, 'COLUMN'),\n(4, 'KEY'),\n(5, 'VIEW'),\n(6, 'USER'),\n(7, 'FUNCTION'),\n(8, 'TRIGGER'),\n(9, 'OWNER'),\n(10, 'INDEX'),\n(11, 'FKEY'),\n(12, 'SEQUENCE'),\n(13, 'PROCEDURE'),\n(14, 'BE_DROPPED'),\n(15, 'TYPE');\nALTER TABLE sys.dependency_types SET READ ONLY;\nGRANT SELECT ON sys.dependency_types TO PUBLIC;\nCREATE VIEW sys.dependencies_vw AS\nSELECT d.id, i1.obj_type, i1.name,\nd.depend_id as used_by_id, i2.obj_type as used_by_obj_type, i2.name as used_by_name,\nd.depend_type, dt.dependency_type_name\nFROM sys.dependencies d\nJOIN sys.ids i1 ON d.id = i1.id\nJOIN sys.ids i2 ON d.depend_id = i2.id\nJOIN sys.dependency_types dt ON d.depend_type = dt.dependency_type_id\nORDER BY id, depend_id;\nGRANT SELECT ON sys.dependencies_vw TO PUBLIC;\n\nCREATE VIEW sys.dependency_owners_on_schemas AS\nSELECT a.name AS owner_name, s.id AS schema_id, s.name AS schema_name, CAST(1 AS smallint) AS depend_type\nFROM sys.schemas AS s, sys.auths AS a\nWHERE s.owner = a.id\nORDER BY a.name, s.name;\nGRANT SELECT ON sys.dependency_owners_on_schemas TO PUBLIC;\n\n\nCREATE VIEW sys.dependency_columns_on_keys AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, c.id AS column_id, c.name AS column_name, k.id AS key_id, k.name AS key_name, CAST(kc.nr +1 AS int) AS key_col_nr, CAST(k.type AS smallint) AS key_type, CAST(4 AS smallint) AS depend_type\nFROM sys.columns AS c, sys.objects AS kc, sys.keys AS k, sys.tables AS t\nWHERE k.table_id = c.table_id AND c.table_id = t.id AND kc.id = k.id AND kc.name = c.name\nAND k.type IN (0, 1)\nORDER BY t.schema_id, t.name, c.name, k.type, k.name, kc.nr;\nGRANT SELECT ON sys.dependency_columns_on_keys TO PUBLIC;\nCREATE VIEW sys.dependency_tables_on_views AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, dep.depend_type AS depend_type\nFROM sys.tables AS t, sys.tables AS v, sys.dependencies AS dep\nWHERE t.id = dep.id AND v.id = dep.depend_id\nAND dep.depend_type = 5 AND t.type NOT IN (1, 11) AND v.type IN (1, 11)\nORDER BY t.schema_id, t.name, v.schema_id, v.name;\nGRANT SELECT ON sys.dependency_tables_on_views TO PUBLIC;\nCREATE VIEW sys.dependency_views_on_views AS\nSELECT v1.schema_id AS view1_schema_id, v1.id AS view1_id, v1.name AS view1_name, v2.schema_id AS view2_schema_id, v2.id AS view2_id, v2.name AS view2_name, dep.depend_type AS depend_type\nFROM sys.tables AS v1, sys.tables AS v2, sys.dependencies AS dep\nWHERE v1.id = dep.id AND v2.id = dep.depend_id\nAND dep.depend_type = 5 AND v1.type IN (1, 11) AND v2.type IN (1, 11)\nORDER BY v1.schema_id, v1.name, v2.schema_id, v2.name;\nGRANT SELECT ON sys.dependency_views_on_views TO PUBLIC;\nCREATE VIEW sys.dependency_columns_on_views AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, c.id AS column_id, c.name AS column_name, v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, dep.depend_type AS depend_type\nFROM sys.columns AS c, sys.tables AS v, sys.tables AS t, sys.dependencies AS dep\nWHERE c.id = dep.id AND v.id = dep.depend_id AND c.table_id = t.id\nAND dep.depend_type = 5 AND v.type IN (1, 11)\nORDER BY t.schema_id, t.name, c.name, v.name;\nGRANT SELECT ON sys.dependency_columns_on_views TO PUBLIC;\nCREATE VIEW sys.dependency_functions_on_views AS\nSELECT f.schema_id AS function_schema_id, f.id AS function_id, f.name AS function_name, v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, dep.depend_type AS depend_type\nFROM sys.functions AS f, sys.tables AS v, sys.dependencies AS dep\nWHERE f.id = dep.id AND v.id = dep.depend_id\nAND dep.depend_type = 5 AND v.type IN (1, 11)\nORDER BY f.schema_id, f.name, v.schema_id, v.name;\nGRANT SELECT ON sys.dependency_functions_on_views TO PUBLIC;\nCREATE VIEW sys.dependency_schemas_on_users AS\nSELECT s.id AS schema_id, s.name AS schema_name, u.name AS user_name, CAST(6 AS smallint) AS depend_type\nFROM sys.users AS u, sys.schemas AS s\nWHERE u.default_schema = s.id\nORDER BY s.name, u.name;\nGRANT SELECT ON sys.dependency_schemas_on_users TO PUBLIC;\nCREATE VIEW sys.dependency_tables_on_functions AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\nFROM sys.functions AS f, sys.tables AS t, sys.dependencies AS dep\nWHERE t.id = dep.id AND f.id = dep.depend_id\nAND dep.depend_type = 7 AND f.type <> 2 AND t.type NOT IN (1, 11)\nORDER BY t.name, t.schema_id, f.name, f.id;\nGRANT SELECT ON sys.dependency_tables_on_functions TO PUBLIC;\nCREATE VIEW sys.dependency_views_on_functions AS\nSELECT v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\nFROM sys.functions AS f, sys.tables AS v, sys.dependencies AS dep\nWHERE v.id = dep.id AND f.id = dep.depend_id\nAND dep.depend_type = 7 AND f.type <> 2 AND v.type IN (1, 11)\nORDER BY v.name, v.schema_id, f.name, f.id;\nGRANT SELECT ON sys.dependency_views_on_functions TO PUBLIC;\nCREATE VIEW sys.dependency_columns_on_functions AS\nSELECT c.table_id, c.id AS column_id, c.name, f.id AS function_id, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\nFROM sys.functions AS f, sys.columns AS c, sys.dependencies AS dep\nWHERE c.id = dep.id AND f.id = dep.depend_id\nAND dep.depend_type = 7 AND f.type <> 2\nORDER BY c.name, c.table_id, f.name, f.id;\nGRANT SELECT ON sys.dependency_columns_on_functions TO PUBLIC;\nCREATE VIEW sys.dependency_functions_on_functions AS\nSELECT f1.schema_id, f1.id AS function_id, f1.name AS function_name, f1.type AS function_type,\nf2.schema_id AS used_in_function_schema_id, f2.id AS used_in_function_id, f2.name AS used_in_function_name, f2.type AS used_in_function_type, dep.depend_type AS depend_type\nFROM sys.functions AS f1, sys.functions AS f2, sys.dependencies AS dep\nWHERE f1.id = dep.id AND f2.id = dep.depend_id\nAND dep.depend_type = 7 AND f2.type <> 2\nORDER BY f1.name, f1.id, f2.name, f2.id;\nGRANT SELECT ON sys.dependency_functions_on_functions TO PUBLIC;\nCREATE VIEW sys.dependency_tables_on_triggers AS\n(SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, tri.id AS trigger_id, tri.name AS trigger_name, CAST(8 AS smallint) AS depend_type\nFROM sys.tables AS t, sys.triggers AS tri\nWHERE tri.table_id = t.id)\nUNION\n(SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, tri.id AS trigger_id, tri.name AS trigger_name, dep.depend_type AS depend_type\nFROM sys.tables AS t, sys.triggers AS tri, sys.dependencies AS dep\nWHERE dep.id = t.id AND dep.depend_id = tri.id\nAND dep.depend_type = 8)\nORDER BY table_schema_id, table_name, trigger_name;\nGRANT SELECT ON sys.dependency_tables_on_triggers TO PUBLIC;\nCREATE VIEW sys.dependency_columns_on_triggers AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, tri.id AS trigger_id, tri.name AS trigger_name, c.id AS column_id, c.name AS column_name, dep.depend_type AS depend_type\nFROM sys.tables AS t, sys.columns AS c, sys.triggers AS tri, sys.dependencies AS dep\nWHERE dep.id = c.id AND dep.depend_id = tri.id AND c.table_id = t.id\nAND dep.depend_type = 8\nORDER BY t.schema_id, t.name, tri.name, c.name;\nGRANT SELECT ON sys.dependency_columns_on_triggers TO PUBLIC;\nCREATE VIEW sys.dependency_functions_on_triggers AS\nSELECT f.schema_id AS function_schema_id, f.id AS function_id, f.name AS function_name, f.type AS function_type,\ntri.id AS trigger_id, tri.name AS trigger_name, tri.table_id AS trigger_table_id, dep.depend_type AS depend_type\nFROM sys.functions AS f, sys.triggers AS tri, sys.dependencies AS dep\nWHERE dep.id = f.id AND dep.depend_id = tri.id\nAND dep.depend_type = 8\nORDER BY f.schema_id, f.name, tri.name;\nGRANT SELECT ON sys.dependency_functions_on_triggers TO PUBLIC;\n\nCREATE VIEW sys.dependency_tables_on_indexes AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, i.id AS index_id, i.name AS index_name, i.type AS index_type, CAST(10 AS smallint) AS depend_type\nFROM sys.tables AS t, sys.idxs AS i\nWHERE i.table_id = t.id\n AND (i.table_id, i.name) NOT IN (SELECT k.table_id, k.name FROM sys.keys k)\nORDER BY t.schema_id, t.name, i.name;\nGRANT SELECT ON sys.dependency_tables_on_indexes TO PUBLIC;\nCREATE VIEW sys.dependency_columns_on_indexes AS\nSELECT c.id AS column_id, c.name AS column_name, t.id AS table_id, t.name AS table_name, t.schema_id, i.id AS index_id, i.name AS index_name, i.type AS index_type, CAST(ic.nr +1 AS INT) AS seq_nr, CAST(10 AS smallint) AS depend_type\nFROM sys.tables AS t, sys.columns AS c, sys.objects AS ic, sys.idxs AS i\nWHERE ic.name = c.name AND ic.id = i.id AND c.table_id = i.table_id AND c.table_id = t.id\n AND (i.table_id, i.name) NOT IN (SELECT k.table_id, k.name FROM sys.keys k)\nORDER BY c.name, t.name, t.schema_id, i.name, ic.nr;\nGRANT SELECT ON sys.dependency_columns_on_indexes TO PUBLIC;\nCREATE VIEW sys.dependency_tables_on_foreignkeys AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, fk.name AS fk_name, CAST(k.type AS smallint) AS key_type, CAST(11 AS smallint) AS depend_type\nFROM sys.tables AS t, sys.keys AS k, sys.keys AS fk\nWHERE fk.rkey = k.id and k.table_id = t.id\nORDER BY t.schema_id, t.name, fk.name;\nGRANT SELECT ON sys.dependency_tables_on_foreignkeys TO PUBLIC;\nCREATE VIEW sys.dependency_keys_on_foreignkeys AS\nSELECT k.table_id AS key_table_id, k.id AS key_id, k.name AS key_name, fk.table_id AS fk_table_id, fk.id AS fk_id, fk.name AS fk_name, CAST(k.type AS smallint) AS key_type, CAST(11 AS smallint) AS depend_type\nFROM sys.keys AS k, sys.keys AS fk\nWHERE k.id = fk.rkey\nORDER BY k.name, fk.name;\nGRANT SELECT ON sys.dependency_keys_on_foreignkeys TO PUBLIC;\n\nCREATE VIEW sys.dependency_tables_on_procedures AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\nFROM sys.functions AS p, sys.tables AS t, sys.dependencies AS dep\nWHERE t.id = dep.id AND p.id = dep.depend_id\nAND dep.depend_type = 13 AND p.type = 2 AND t.type NOT IN (1, 11)\nORDER BY t.name, t.schema_id, p.name, p.id;\nGRANT SELECT ON sys.dependency_tables_on_procedures TO PUBLIC;\nCREATE VIEW sys.dependency_views_on_procedures AS\nSELECT v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\nFROM sys.functions AS p, sys.tables AS v, sys.dependencies AS dep\nWHERE v.id = dep.id AND p.id = dep.depend_id\nAND dep.depend_type = 13 AND p.type = 2 AND v.type IN (1, 11)\nORDER BY v.name, v.schema_id, p.name, p.id;\nGRANT SELECT ON sys.dependency_views_on_procedures TO PUBLIC;\nCREATE VIEW sys.dependency_columns_on_procedures AS\nSELECT c.table_id, c.id AS column_id, c.name AS column_name, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\nFROM sys.functions AS p, sys.columns AS c, sys.dependencies AS dep\nWHERE c.id = dep.id AND p.id = dep.depend_id\nAND dep.depend_type = 13 AND p.type = 2\nORDER BY c.name, c.table_id, p.name, p.id;\nGRANT SELECT ON sys.dependency_columns_on_procedures TO PUBLIC;\nCREATE VIEW sys.dependency_functions_on_procedures AS\nSELECT f.schema_id AS function_schema_id, f.id AS function_id, f.name AS function_name, f.type AS function_type,\np.schema_id AS procedure_schema_id, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\nFROM sys.functions AS p, sys.functions AS f, sys.dependencies AS dep\nWHERE f.id = dep.id AND p.id = dep.depend_id\nAND dep.depend_type = 13 AND p.type = 2\nORDER BY p.name, p.id, f.name, f.id;\nGRANT SELECT ON sys.dependency_functions_on_procedures TO PUBLIC;\n\nCREATE VIEW sys.dependency_columns_on_types AS\nSELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, dt.id AS type_id, dt.sqlname AS type_name, c.id AS column_id, c.name AS column_name, dep.depend_type AS depend_type\nFROM sys.tables AS t, sys.columns AS c, sys.types AS dt, sys.dependencies AS dep\nWHERE dep.id = dt.id AND dep.depend_id = c.id AND c.table_id = t.id\nAND dep.depend_type = 15\nORDER BY dt.sqlname, t.name, c.name, c.id;\nGRANT SELECT ON sys.dependency_columns_on_types TO PUBLIC;\nCREATE VIEW sys.dependency_functions_on_types AS\nSELECT dt.id AS type_id, dt.sqlname AS type_name, f.id AS function_id, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\nFROM sys.functions AS f, sys.types AS dt, sys.dependencies AS dep\nWHERE dep.id = dt.id AND dep.depend_id = f.id\nAND dep.depend_type = 15\nORDER BY dt.sqlname, f.name, f.id;\nGRANT SELECT ON sys.dependency_functions_on_types TO PUBLIC;\nCREATE VIEW sys.dependency_args_on_types AS\nSELECT dt.id AS type_id, dt.sqlname AS type_name, f.id AS function_id, f.name AS function_name, a.id AS arg_id, a.name AS arg_name, a.number AS arg_nr, dep.depend_type AS depend_type\nFROM sys.args AS a, sys.functions AS f, sys.types AS dt, sys.dependencies AS dep\nWHERE dep.id = dt.id AND dep.depend_id = a.id AND a.func_id = f.id\nAND dep.depend_type = 15\nORDER BY dt.sqlname, f.name, a.number, a.name;\nGRANT SELECT ON sys.dependency_args_on_types TO PUBLIC;\n" }, 
