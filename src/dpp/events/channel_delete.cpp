#include <dpp/discord.h>
#include <dpp/event.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dpp/discordclient.h>
#include <dpp/discordevents.h>
#include <dpp/discord.h>
#include <dpp/cache.h>
#include <dpp/stringops.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


namespace dpp { namespace events {

using namespace dpp;

/**
 * @brief Handle event
 * 
 * @param client Websocket client (current shard)
 * @param j JSON data for the event
 * @param raw Raw JSON string
 */
void channel_delete::handle(DiscordClient* client, json &j, const std::string &raw) {
	json& d = j["d"];
	dpp::channel* c = dpp::find_channel(SnowflakeNotNull(&d, "id"));
	if (c) {
		dpp::guild* g = dpp::find_guild(c->guild_id);
		if (g) {
			auto gc = std::find(g->channels.begin(), g->channels.end(), c->id);
			if (gc != g->channels.end()) {
				g->channels.erase(gc);
			}

			if (client->creator->dispatch.channel_delete) {
				dpp::channel_delete_t cd(raw);
				cd.deleted = c;
				cd.deleting_guild = g;
				client->creator->dispatch.channel_delete(cd);
			}
		}
		dpp::get_channel_cache()->remove(c);
	}
}

}};