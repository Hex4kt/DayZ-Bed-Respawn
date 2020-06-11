class CustomMission: MissionServer
{
	// ------------------------------------------------------------
	// Override PlayerBase CreateCharacter
	// ------------------------------------------------------------
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		
		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	// ------------------------------------------------------------
	// Override StartingEquipSetup
	// ------------------------------------------------------------
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		PlayerIdentity id = player.GetIdentity();
		BedFrameWork.FixSpawningHeight( player, BedFrameWork.AttemptBedSpawn( id,player.GetPosition() ) );
		BedFrameWork.BreakOldSpawnBed( id, BedFrameWork.AttemptBedSpawn( id,player.GetPosition() ) );
		
		if ( GetExpansionSettings() && GetExpansionSettings().GetSpawn() && GetExpansionSettings().GetSpawn().StartingGear.UseStartingGear )
		{
			SetStartingGear(player);
		}
		else
		{
			EntityAI itemTop;
			EntityAI itemEnt;
			ItemBase itemBs;
			float rand;
			
			itemTop = player.FindAttachmentBySlotName("Body");
			
			if ( itemTop )
			{
				itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
				if ( Class.CastTo(itemBs, itemEnt ) )
					itemBs.SetQuantity(4);

				SetRandomHealth(itemEnt);
				
				itemEnt = itemTop.GetInventory().CreateInInventory("RoadFlare");
				SetRandomHealth(itemEnt);
				
				rand = Math.RandomFloatInclusive(0.0, 1.0);
				if ( rand < 0.35 )
					itemEnt = player.GetInventory().CreateInInventory("Apple");
				else if ( rand > 0.65 )
					itemEnt = player.GetInventory().CreateInInventory("Pear");
				else
					itemEnt = player.GetInventory().CreateInInventory("Plum");
			
				SetRandomHealth(itemEnt);
			}
		}
	}
}