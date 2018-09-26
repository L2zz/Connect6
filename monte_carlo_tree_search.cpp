#include "monte_carlo_tree_search.h"
using namespace std;

// TO DO List
// SelectionAndExpansion Implementation
// Evaluation random index Selection
// VirtualPlay Implementation


Position MonteCarloTreeSearch(State& current, double recv_time) {
  // Calculate start time
  chrono::system_clock::time_point start = chrono::system_clock::now();

  // Modify received time to return safe
  recv_time -= TERMINIATE_TIME_PADDING;
  Position best_pos;
  int win_count;

  // Play game virtually during received time
  while ((chrono::duration<double>(chrono::system_clock::now() - start).count() < recv_time) {
    State& best_child = current.SelectionAndExpansion();
    win_count = best_child.Evaluation();
    best_child.Update(win_count);
    best_pos = current.BestChoice();
  }
  return best_pos;
}

State& State::SelectionAndExpansion() {
  // If all children are visited, then go to best child.
  // If there are children to check, then select it and expand children.
  for (int i = 0; i < mct_const::NUMBER_OF_MAX_CHILD_NODES; i++) {
    if () {


    } else {


    }
  }
}

int State::Evaluation() {
  int win_count = 0;
  thread** thread_list = new thread*[mct_const::NUMBER_OF_THREADS];

  // Select random index of child child_list_
  //
  for (int i = 0; i < mct_const::NUMBER_OF_THREADS; i++) {
    thread_list[i] = new thread(child_list_[i]->VirtualPlay, win_count);
  }

  for (int i = 0; i < mct_const::NUMBER_OF_THREADS; i++) {
    thread_list[i]->join();
  }
  delete[] thread_list;

  return win_count;
}

void State::VirtualPlay(int& win_count) {

}

void State::Update(int result) {
  number_of_wins_ += result;
  number_of_visiting_ += mct_const::NUMBER_OF_THREADS;
  parent_->Update();
}

Position State::BestChoice() {
  int max_idx = 0;
  int change_pos;
  double max_avg_wins = (double)(child_list_[0]->number_of_wins_) / (child_list_[0]->number_of_visiting_);
  for (int i = 1; i < mct_const::NUMBER_OF_MAX_CHILD_NODES; i++) {
    int avg_wins = (double)(child_list_[i]->number_of_wins_) / (child_list_[i]->number_of_visiting_);
    if (max_avg_wins < avg_wins) {
      max_avg_wins = avg_wins;
      max_idx = i;
    }
  }

  change_pos = child_list_[max_idx]->change_idx_;
  Position ret_pos = Position(change_pos % 19, change_pos / 19);
  return ret_pos;
}
