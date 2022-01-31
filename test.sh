#!/bin/bash

if [ "$1" == "clean" ] 
then
  rm -f ft_out
  rm -f stl_out
  make fclean
  exit 0
fi

make

echo "FT  TIME : "
time ./ft_containers > ft_out
echo "STD TIME : "
time ./stl_containers > stl_out

output=$(diff ft_out stl_out)

if [ "$output" ]
then
  echo "Error: see diff"
  echo "$output"
else
  echo "All good! No errors."
  make fclean &> /dev/null
  rm -f ft_out &> /dev/null
  rm -f stl_out &> /dev/null
fi