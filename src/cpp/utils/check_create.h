#pragma once
#include <string>
#include <optional>
#include "pdf/Pdf.h"


std::optional<pdf::Pdf> check_create(const std::string& inp_file) noexcept;