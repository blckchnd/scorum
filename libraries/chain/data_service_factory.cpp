#include <scorum/chain/data_service_factory.hpp>

#include <scorum/chain/database.hpp>

#include <scorum/chain/dbs_account.hpp>
#include <scorum/chain/dbs_proposal.hpp>
#include <scorum/chain/dbs_registration_committee.hpp>
#include <scorum/chain/dbs_dynamic_global_property.hpp>
#include <scorum/chain/dbs_comment.hpp>
#include <scorum/chain/dbs_decline_voting_rights_request.hpp>
#include <scorum/chain/dbs_witness_vote.hpp>
#include <scorum/chain/dbs_withdraw_vesting_route.hpp>
#include <scorum/chain/dbs_vesting_delegation.hpp>
#include <scorum/chain/dbs_reward_fund.hpp>
#include <scorum/chain/dbs_registration_pool.hpp>
#include <scorum/chain/dbs_witness.hpp>
#include <scorum/chain/dbs_comment_vote.hpp>
#include <scorum/chain/dbs_escrow.hpp>
#include <scorum/chain/dbs_budget.hpp>
#include <scorum/chain/dbs_atomicswap.hpp>

// clang-format off
DATA_SERVICE_FACTORY_IMPL(
        (account)
        (proposal)
        (registration_committee)
        (dynamic_global_property)
        (comment)
        (witness)
        (decline_voting_rights_request)
        (vesting_delegation)
        (witness_vote)
        (withdraw_vesting_route)
        (reward_fund)
        (registration_pool)
        (comment_vote)
        (escrow)
        (budget)
        (atomicswap)
        )
// clang-format on