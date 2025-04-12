BEGIN;

DROP TABLE IF EXISTS persons CASCADE;
CREATE TABLE persons (
    pk bigserial NOT NULL,
    firstname varchar(255) NOT NULL,
    lastname varchar(255) NOT NULL,
    rut bigint NOT NULL,
    birthday date NOT NULL,
    created timestamptz NOT NULL DEFAULT NOW(),
    updated timestamptz NOT NULL DEFAULT NOW(),
    PRIMARY KEY (pk)
);
CREATE UNIQUE INDEX ON persons(rut);


COMMIT;