#include <scorum/chain/services/proposal_executor.hpp>

#include <scorum/chain/services/proposal.hpp>

#include <scorum/chain/evaluators/committee_accessor.hpp>
#include <scorum/chain/evaluators/proposal_evaluators.hpp>

#include <scorum/chain/data_service_factory.hpp>
#include <scorum/chain/schema/proposal_object.hpp>

#include <scorum/protocol/proposal_operations.hpp>

namespace scorum {
namespace chain {

proposal_executor::proposal_executor(data_service_factory_i& s)
    : services(s)
    , proposal_service(services.proposal_service())
    , evaluators(services)
{
    evaluators.register_evaluator<registration_committee::proposal_add_member_evaluator>();
    evaluators.register_evaluator<registration_committee::proposal_change_quorum_evaluator>();
    evaluators.register_evaluator<registration_committee::proposal_exclude_member_evaluator>(
        new registration_committee::proposal_exclude_member_evaluator(services, removed_members));

    evaluators.register_evaluator<development_committee::proposal_add_member_evaluator>();
    evaluators.register_evaluator<development_committee::proposal_change_quorum_evaluator>();
    evaluators.register_evaluator<development_committee::proposal_exclude_member_evaluator>(
        new development_committee::proposal_exclude_member_evaluator(services, removed_members));

    evaluators.register_evaluator<development_committee::proposal_withdraw_vesting_evaluator>();
    evaluators.register_evaluator<development_committee::proposal_transfer_evaluator>();
}

void proposal_executor::operator()(const proposal_object& proposal)
{
    execute_proposal(proposal);
    update_proposals_voting_list_and_execute();
}

bool proposal_executor::is_quorum(const proposal_object& proposal)
{
    committee_i& committee_service = proposal.operation.visit(get_operation_committee_visitor(services));
    const size_t votes = proposal_service.get_votes(proposal);
    const size_t members_count = committee_service.get_members_count();

    return utils::is_quorum(votes, members_count, proposal.quorum_percent);
}

void proposal_executor::execute_proposal(const proposal_object& proposal)
{
    if (is_quorum(proposal))
    {
        auto& evaluator = evaluators.get_evaluator(proposal.operation);
        evaluator.apply(proposal.operation);
        proposal_service.remove(proposal);
    }
}

void proposal_executor::update_proposals_voting_list_and_execute()
{
    while (!removed_members.empty())
    {
        account_name_type member = *removed_members.begin();

        proposal_service.for_all_proposals_remove_from_voting_list(member);

        auto proposals = proposal_service.get_proposals();

        for (const auto& p : proposals)
        {
            execute_proposal(p);
        }

        removed_members.erase(member);
    }
}

} // namespace scorum
} // namespace chain
