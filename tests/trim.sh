#!/bin/bash

echo $1
tr -d " \t" < $1 > $1.tmp
mv -f $1.tmp $1 
