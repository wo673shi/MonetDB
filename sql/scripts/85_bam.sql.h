/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with sql2h.py. Do not edit this file directly.
{ "85_bam", "\nCREATE SCHEMA bam;\nCREATE PROCEDURE bam.bam_loader_repos(bam_repos STRING, dbschema SMALLINT)\nEXTERNAL NAME bam.bam_loader_repos;\nCREATE PROCEDURE bam.bam_loader_files(bam_files STRING, dbschema SMALLINT)\nEXTERNAL NAME bam.bam_loader_files;\nCREATE PROCEDURE bam.bam_loader_file(bam_file STRING, dbschema SMALLINT)\nEXTERNAL NAME bam.bam_loader_file;\nCREATE PROCEDURE bam.bam_drop_file(file_id BIGINT, dbschema SMALLINT)\nEXTERNAL NAME bam.bam_drop_file;\nCREATE FUNCTION bam.bam_flag(flag SMALLINT, name STRING)\nRETURNS BOOLEAN EXTERNAL NAME bam.bam_flag;\nCREATE FUNCTION bam.reverse_seq(seq STRING)\nRETURNS STRING EXTERNAL NAME bam.reverse_seq;\nCREATE FUNCTION bam.reverse_qual(qual STRING)\nRETURNS STRING EXTERNAL NAME bam.reverse_qual;\nCREATE FUNCTION bam.seq_length(cigar STRING)\nRETURNS INT EXTERNAL NAME bam.seq_length;\nCREATE FUNCTION bam.seq_char(ref_pos INT, alg_seq STRING, alg_pos INT, alg_cigar STRING)\nRETURNS CHAR(1) EXTERNAL NAME bam.seq_char;\nCREATE PROCEDURE bam.sam_export(output_path STRING)\nEXTERNAL NAME bam.sam_export;\nCREATE PROCEDURE bam.bam_export(output_path STRING)\nEXTERNAL NAME bam.bam_export;\nCREATE TABLE bam.files (\nfile_id BIGINT NOT NULL,\nfile_location STRING NOT NULL,\ndbschema SMALLINT NOT NULL,\nformat_version VARCHAR(7),\nsorting_order VARCHAR(10),\ncomments STRING,\nCONSTRAINT files_pkey_file_id PRIMARY KEY (file_id)\n);\nCREATE TABLE bam.sq (\nsn STRING NOT NULL,\nfile_id BIGINT NOT NULL,\nln INT,\n\"as\" INT,\nm5 STRING,\nsp STRING,\nur STRING,\nCONSTRAINT sq_pkey_sn_file_id PRIMARY KEY (sn, file_id),\nCONSTRAINT sq_fkey_file_id FOREIGN KEY (file_id) REFERENCES bam.files (file_id)\n);\nCREATE TABLE bam.rg (\nid STRING NOT NULL,\nfile_id BIGINT NOT NULL,\ncn STRING,\nds STRING,\ndt TIMESTAMP,\nfo STRING,\nks STRING,\nlb STRING,\npg STRING,\npi INT,\npl STRING,\npu STRING,\nsm STRING,\nCONSTRAINT rg_pkey_id_file_id PRIMARY KEY (id, file_id),\nCONSTRAINT rg_fkey_file_id FOREIGN KEY (file_id) REFERENCES bam.files (file_id)\n);\nCREATE TABLE bam.pg (\nid STRING NOT NULL,\nfile_id BIGINT NOT NULL,\npn STRING,\ncl STRING,\npp STRING,\nvn STRING,\nCONSTRAINT pg_pkey_id_file_id PRIMARY KEY (id, file_id),\nCONSTRAINT pg_fkey_file_id FOREIGN KEY (file_id) REFERENCES bam.files (file_id)\n);\nCREATE TABLE bam.export (\nqname STRING NOT NULL,\nflag SMALLINT NOT NULL,\nrname STRING NOT NULL,\npos INT NOT NULL,\nmapq SMALLINT NOT NULL,\ncigar STRING NOT NULL,\nrnext STRING NOT NULL,\npnext INT NOT NULL,\ntlen INT NOT NULL,\nseq STRING NOT NULL,\nqual STRING NOT NULL\n);\nGRANT SELECT ON bam.files TO PUBLIC;\nGRANT SELECT ON bam.sq TO PUBLIC;\nGRANT SELECT ON bam.rg TO PUBLIC;\nGRANT SELECT ON bam.pg TO PUBLIC;\nGRANT SELECT ON bam.export TO PUBLIC;\nGRANT EXECUTE ON FUNCTION bam.bam_flag(SMALLINT, STRING) TO PUBLIC;\nGRANT EXECUTE ON FUNCTION bam.reverse_seq(STRING) TO PUBLIC;\nGRANT EXECUTE ON FUNCTION bam.reverse_qual(STRING) TO PUBLIC;\nGRANT EXECUTE ON FUNCTION bam.seq_length(STRING) TO PUBLIC;\nGRANT EXECUTE ON FUNCTION bam.seq_char(INT, STRING, INT, STRING) TO PUBLIC;\nGRANT EXECUTE ON PROCEDURE bam.bam_loader_repos(STRING, SMALLINT) TO PUBLIC;\nGRANT EXECUTE ON PROCEDURE bam.bam_loader_files(STRING, SMALLINT) TO PUBLIC;\nGRANT EXECUTE ON PROCEDURE bam.bam_loader_file(STRING, SMALLINT) TO PUBLIC;\nGRANT EXECUTE ON PROCEDURE bam.bam_drop_file(BIGINT, SMALLINT) TO PUBLIC;\nGRANT EXECUTE ON PROCEDURE bam.sam_export(STRING) TO PUBLIC;\nGRANT EXECUTE ON PROCEDURE bam.bam_export(STRING) TO PUBLIC;" }, 
