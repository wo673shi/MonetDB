#!/usr/bin/env perl

use strict;
use warnings;

$|++;

use DBI();

my $dbh = DBI->connect(
    "dbi:monetdb:host=$ARGV[2];port=$ARGV[0];database=$ARGV[1]", 'monetdb', 'monetdb'
);

my $query = qq{
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
UNION ALL
SELECT * FROM tables
};

my $sth = $dbh->prepare($query);
$sth->execute;

my $r = $sth->fetchall_arrayref();

$dbh->disconnect();
