CREATE TABLE testing9 (abc INT);

CREATE TRIGGER test9 AFTER INSERT ON testing9 FOR EACH STATEMENT BEGIN ATOMIC INSERT INTO testing9 VALUES (1); END;

DROP TRIGGER test9;
DROP TRIGGER IF EXISTS test9;
DROP TRIGGER test9; --should fail

DROP TABLE testing9;
