#!/bin/bash

# psql --username=ainr --host=localhost --dbname=huidb < player.sql ^C

odb -d pgsql --generate-query --generate-schema --generate-session ../player.hxx
