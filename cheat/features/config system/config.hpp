#pragma once
#include <vector>
#include <fstream>
#include <filesystem>
#include <string_view>

#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../helpers/singleton.hpp"
#include "../../helpers/nlohmann/json.hpp"
#include "../../helpers/nlohmann/json_fwd.hpp"

class configsystem : public singleton<configsystem>
{
public:
	void create_directory();
	void update_configs();
	void create_file(const std::string_view name);
	void delete_file(const std::size_t index);
	void save(const std::size_t index);
	void load(const std::size_t index);

	std::vector<std::string> configs;
};