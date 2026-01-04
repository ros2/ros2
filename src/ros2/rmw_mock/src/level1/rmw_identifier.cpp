// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// rmw_mock: Implementation identifier and serialization format

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"

extern "C" {

RMW_MOCK_PUBLIC
const char * rmw_get_implementation_identifier(void)
{
  return rmw_mock::RMW_MOCK_IDENTIFIER;
}

RMW_MOCK_PUBLIC
const char * rmw_get_serialization_format(void)
{
  return rmw_mock::RMW_MOCK_SERIALIZATION_FORMAT;
}

}  // extern "C"
