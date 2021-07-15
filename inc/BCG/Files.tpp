// ========================================================================== //
// local macro

#define THROWTEXT(msg) (std::string("RUNTIME EXCEPTION IN ") + (__PRETTY_FUNCTION__) + "\n" + msg)

// ========================================================================== //
// procs

static inline std::fstream BCG::openThrow(const std::string & filename,
                                          const std::ios_base::openmode mode,
                                          bool noOverwrite) {
  if (noOverwrite && mode != std::fstream::in) {
    if (std::filesystem::exists(filename)) {
      throw std::filesystem::filesystem_error(THROWTEXT("    File '" + filename + "' already exists!"),
                                              std::error_code(static_cast<int>(std::errc::no_such_file_or_directory), std::system_category())
                                             );
    }
  }

  auto reVal = std::fstream(filename, mode);

  if ( !reVal.is_open() ) {
    throw( std::invalid_argument("failed to open '" + filename + "'") );
    throw std::filesystem::filesystem_error(THROWTEXT("    Failed to open '" + filename + "'"),
                                            std::error_code(static_cast<int>(std::errc::no_such_file_or_directory), std::system_category())
                                           );
  }

  return reVal;
}
// ........................................................................ //
static inline std::string  BCG::generateFileComments(const std::string & content) {
  std::string reVal;

  reVal += "# ============================================================================ #\n";
  auto lines = BCG::splitString(content, '\n');
  for (const auto & line : lines) {reVal += "# " + line + "\n";}
  reVal += "# timestamp: ";
  reVal +=    generateTimestamp() + "\n";
  reVal += "# ============================================================================ #\n\n";

  return reVal;
}

// ========================================================================== //

#undef THROWTEXT



