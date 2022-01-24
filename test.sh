#!/bin/bash

if [ "$1" == "clean" ] 
then
  rm -f ft_out
  rm -f stl_out
  make fclean
  exit 0
fi

make

./ft_containers > ft_out
./stl_containers > stl_out

output=$(diff ft_out stl_out)

# shellcheck disable=SC1009


if [ "$output" ]
then
  echo "Error: see diff"
  echo "$output"
else
  make fclean
  rm -f ft_out
  rm -f stl_out
fi