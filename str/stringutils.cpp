#include "stringutils.h"

namespace stringutils {

void splitFilename(const std::string &filename,
                   std::string &base,
                   std::string &filename_wo_ext,
                   std::string &ext) {
  if (filename.empty()) return;
  auto dir_idx = filename.rfind('/');
  std::string filename_w_ext;
  if (dir_idx != std::string::npos) {
    base = filename.substr(0, dir_idx + 1);
    filename_w_ext = filename.substr(dir_idx + 1);
  } else {
    base = "./";
    filename_w_ext = filename;
  }
  auto ext_idx = filename_w_ext.rfind('.');
  filename_wo_ext = filename_w_ext.substr(0, ext_idx);
  if (ext_idx != std::string::npos)
    ext = filename_w_ext.substr(ext_idx);
}

/**
 * ../syn/events2_U100_I10_T100.dat -->
 * ../syn/events2_U100_I10_T100_test.dat
 */
std::string insertMiddle(const std::string &filename,
                         const std::string &sufix) {
  auto idx = filename.rfind('.');
  if (idx != std::string::npos) {
    std::string extension = filename.substr(idx + 1);
    std::string base = filename.substr(0, idx);
    return base + "_" + sufix + "." + extension;
  } else
    return filename + "_" + sufix;
}

std::string getBasePath(const std::string &filename) {
  auto idx = filename.rfind('/');
  if (idx != std::string::npos) {
    return filename.substr(0, idx + 1);
  } else {
    return "./";
  }
}

std::string prettyNumber(const int num) {
  if (num < 1e3)
    return fmt::format("{}", num);
  else if (num < 1e6)
    return fmt::format("{}K", num / 1000);
  else if (num < 1e9)
    return fmt::format("{}M", num / 1000000);
  else
    return fmt::format("{}G", num / 1000000000);
}

std::string prettySize(const int size) {
  if (size < Kilobytes)
    return fmt::format("{}B", size);
  else if (size < Megabytes)
    return fmt::format("{:.2f}K", size / Kilobytes);
  else if (size < Gigabytes)
    return fmt::format("{:.2f}M", size / Megabytes);
  else
    return fmt::format("{:.2f}G", size / Gigabytes);
}

void split(const std::string &s, const char delim,
           std::vector<std::string> &elems) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) elems.push_back(item);
}

std::vector<std::string> split(const std::string &s,
                               const char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}
}
