#!/bin/bash

go build $(cd `dirname $0`; pwd)/test.go

mv ./test ~/test