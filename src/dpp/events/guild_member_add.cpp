/************************************************************************************
 *
 * D++, A Lightweight C++ library for Discord
 *
 * Copyright 2021 Craig Edwards and D++ contributors 
 * (https://github.com/brainboxdotcc/DPP/graphs/contributors)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/
#include <dpp/discord.h>
#include <dpp/event.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dpp/discordclient.h>
#include <dpp/discord.h>
#include <dpp/cache.h>
#include <dpp/stringops.h>
#include <nlohmann/json.hpp>
#include <dpp/discordevents.h>

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
void guild_member_add::handle(DiscordClient* client, json &j, const std::string &raw) {
	json d = j["d"];

	dpp::guild* g = dpp::find_guild(SnowflakeNotNull(&d, "guild_id"));
	if (g) {
		dpp::user* u = dpp::find_user(SnowflakeNotNull(&(d["user"]), "id"));
		if (!u) {
			u = new dpp::user();
			u->fill_from_json(&(d["user"]));
			dpp::get_user_cache()->store(u);
		} else {
			u->refcount++;
		}
		dpp::guild_member* gm = new dpp::guild_member();
		gm->fill_from_json(&d, g, u);
		g->members[u->id] = gm;

		if (client->creator->dispatch.guild_member_add) {
			dpp::guild_member_add_t gmr(client, raw);
			gmr.adding_guild = g;
			gmr.added = gm;
			client->creator->dispatch.guild_member_add(gmr);
		}
	}
}

}};