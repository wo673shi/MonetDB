CREATE SCHEMA TB;

CREATE TABLE TB.STOCK_ITEM (
  S_W_ID INTEGER NOT NULL,
  S_I_ID INTEGER NOT NULL,
  S_QUANTITY INTEGER NOT NULL,
  S_DIST_01 CHAR(24) NOT NULL,
  S_DIST_02 CHAR(24) NOT NULL,
  S_DIST_03 CHAR(24) NOT NULL,
  S_DIST_04 CHAR(24) NOT NULL,
  S_DIST_05 CHAR(24) NOT NULL,
  S_DIST_06 CHAR(24) NOT NULL,
  S_DIST_07 CHAR(24) NOT NULL,
  S_DIST_08 CHAR(24) NOT NULL,
  S_DIST_09 CHAR(24) NOT NULL ,
  S_DIST_10 CHAR(24) NOT NULL,
  S_YTD DECIMAL(8,0) NOT NULL,
  S_ORDER_CNT INTEGER NOT NULL,
  S_REMOTE_CNT INTEGER NOT NULL,
  S_DATA VARCHAR(50) NOT NULL
);

PREPARE
UPDATE TB.STOCK_ITEM SET
  S_QUANTITY = ?,
  S_YTD = S_YTD + ?,
  S_ORDER_CNT = S_ORDER_CNT + 1
WHERE S_W_ID = ? AND S_I_ID = ?;

drop table TB.STOCK_ITEM;

drop schema TB;
