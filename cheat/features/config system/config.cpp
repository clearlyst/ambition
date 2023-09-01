#include "config.hpp"

static std::string path = "weiamware/";
static const std::filesystem::path path_fs = "weiamware";

template <typename T>
static void read_value(const nlohmann::json& src, T& dest)
{
	if (src.is_null())
		return;

	dest = src.get<T>();
}

template <typename T>
static T read_value(const nlohmann::json& src)
{
	if (src.is_null())
		return T{};

	return src.get<T>();
}

template <typename T>
static void write_value(nlohmann::json& dest, const T& src)
{
	dest = src;
}

void configsystem::create_directory()
{
	if (!std::filesystem::exists(path_fs))
	{
		std::filesystem::create_directory(path_fs);
	}
	else
	{
		update_configs();
	}
}

void configsystem::update_configs()
{
	configs.clear();

	for (const auto& entry : std::filesystem::directory_iterator{ path_fs })
	{
		if (!entry.is_regular_file() || entry.path().extension() != xorstr(".json"))
		{
			continue;
		}

		const auto& file_name = entry.path().stem().string();
		configs.emplace_back(file_name);
	}
}

void configsystem::create_file(const std::string_view name)
{
	if (name.empty() || name.find_first_not_of(' ') == std::string_view::npos)
	{
		return;
	}

	if (std::find(configs.cbegin(), configs.cend(), name) != configs.cend())
	{
		return;
	}

	configs.emplace_back(name);
	save(configs.size() - 1);
}

void configsystem::delete_file(const std::size_t index)
{
	if (configs.size() <= index)
	{
		return;
	}

	path.append(configs.at(index));
	path.append(xorstr(".json"));
	std::filesystem::remove(path);
	path.erase(path.size() - configs.at(index).size() - 5);

	configs.erase(configs.cbegin() + index);
	configs.shrink_to_fit();
}

void configsystem::save(const std::size_t index)
{
	nlohmann::json json;

	write_value(json[("misc")][("watermark")], variables::config::misc::watermark);
	write_value(json[("misc")][("spectator_list")], variables::config::misc::spectatorlist);

	path.append(configs.at(index));

	const bool has_json_in_filename = path.rfind(xorstr(".json")) != std::string::npos;

	if (!has_json_in_filename)
	{
		path.append(xorstr(".json"));
	}

	if (std::ofstream output_file{ path }; output_file.good())
	{
		output_file << std::setw(4) << json;
	}

	path.erase(path.size() - configs.at(index).size() - (!has_json_in_filename ? 5 : 0));
}

void configsystem::load(const std::size_t index)
{
	path.append(configs.at(index));
	path.append(xorstr(".json"));

	if (std::ifstream input_file{ path }; input_file.good())
	{
		nlohmann::json json;
		input_file >> json;

		read_value(json[("misc")][("watermark")], variables::config::misc::watermark);
		read_value(json[("misc")][("spectator_list")], variables::config::misc::spectatorlist);

	}

	path.erase(path.size() - configs.at(index).size() - 5);
}