// Petit utilitaire d'affichage console (couleurs + troncature)
#ifndef CONSOLE_FORMAT_H
#define CONSOLE_FORMAT_H
#include <string>

namespace ConsoleFmt
{
  // Couleurs ANSI simples (désactivables facilement si besoin)
  inline constexpr const char *RESET = "\033[0m";
  inline constexpr const char *BOLD = "\033[1m";
  inline constexpr const char *DIM = "\033[2m";
  inline constexpr const char *RED = "\033[31m";
  inline constexpr const char *GREEN = "\033[32m";
  inline constexpr const char *YELLOW = "\033[33m";
  inline constexpr const char *BLUE = "\033[34m";
  inline constexpr const char *MAGENTA = "\033[35m";
  inline constexpr const char *CYAN = "\033[36m";

  inline std::string trunc(const std::string &text, std::size_t maxLen)
  {
    if (text.size() <= maxLen)
      return text;
    if (maxLen <= 1)
      return text.substr(0, maxLen);
    return text.substr(0, maxLen - 1) + "…"; // ellipsis unicode
  }
}

#endif // CONSOLE_FORMAT_H
