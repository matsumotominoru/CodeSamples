WHENEVER SQLERROR EXIT SQL.SQLCODE ROLLBACK

CREATE TABLE DCTCSKH01 (
        OSRS_NO                       NUMBER(09)     NOT NULL, -- お知らせ番号
        TITLE_NO                      NUMBER(09)     NOT NULL, -- ﾀｲﾄﾙ番号
        SUB_TITLE_NO                  NUMBER(09)     NOT NULL, -- ｻﾌﾞﾀｲﾄ
        OSRS_KBN                      CHAR(01)       NOT NULL, -- お知らせ区分
        KEIYK_TANI_CD                 CHAR(07)       NOT NULL, -- 契約単位ｺｰ
        KSAI_STAT_D                   CHAR(8)        NOT NULL, -- 掲載開始日
        KSAI_STAT_TIME                CHAR(4)        NOT NULL, -- 掲載開始時刻
        KSAI_END_D                    CHAR(8)        NOT NULL, -- 掲載終了日
        KSAI_END_TIME                 CHAR(4)        NOT NULL, -- 掲載終了時刻
        OSRS_HNBN                     VARCHAR2(2000) NOT NULL, -- お知らせ本文
        SNKI_FLG                      CHAR(01)       NOT NULL, -- 新規ﾌﾗｸﾞ
        SKJO_FLG                      CHAR(01)       NOT NULL, -- 削除ﾌﾗｸﾞ
        TORK_D                        CHAR(8)        NOT NULL, -- 登録日
        TORK_TIME                     CHAR(4)        NOT NULL, -- 登録時刻
        KOSIN_D                       CHAR(8)        NOT NULL, -- 更新日
        KOSIN_TIME                    CHAR(4)        NOT NULL, -- 更新時刻
        KOSIN_PGM_ID                  CHAR(08)       not null, -- 更新ﾌﾟﾛｸ
        KOSIN_USER_ID                 CHAR(08)       not null, -- 更新ﾕ-ｻﾞ
        REC_SAKSE_YMD                 CHAR(08)       not null, -- ﾚｺ-ﾄﾞ作
        REC_KOSIN_YMD                 CHAR(08)       not null, -- ﾚｺ-ﾄﾞ更
        KOSIN_KBN                     CHAR(01)       not null, -- 更新区分
        TIME_STAMP                    CHAR(14)       not null  -- ﾀｲﾑｽﾀﾝ
        )
                                TABLESPACE   B1CZMTBL
                                PCTFREE      10
                                PCTUSED      75
                                STORAGE (    
                                                  INITIAL      1M
                                                  PCTINCREASE  0
                                        )    
/

-- オブジェクト権限設定
GRANT SELECT ON DCTCSKH01 TO OPS$DBUSER;
GRANT INSERT, DELETE, UPDATE, SELECT ON DCTCSKH01 TO OPS$DBADMIN;

COMMIT
/
EXIT
