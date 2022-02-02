#!/bin/bash

if [ "$1" == "clean" ] 
then
  rm -f ft_out
  rm -f stl_out
  make fclean > /dev/null
  make -C tests fclean > /dev/null
  exit 0
fi

make > /dev/null

./ft_containers > ft_out
./stl_containers > stl_out

output=$(diff ft_out stl_out)

if [ "$output" ]
then
  echo "Result: FAILURE"
  echo "$output"
else
  make -C tests > /dev/null
  ./tests/time_it stl_containers ft_containers
  make -C tests fclean > /dev/null
  echo "Result: OK"
  make fclean &> /dev/null
  rm -f ft_out &> /dev/null
  rm -f stl_out &> /dev/null
fi