<?php
// $id$

/**
 * @file
 * This file contains the api functions which developers can use to
 * influence the serendipity results.
 */

/**
 * Hook to define a serendipity "action"
 * 
 * @return array
 */
function hook_serendipity_info() {
  return array(
    'machine_name' => array(
      'title' => 'some title', // Required
      'description' => 'A nice informative description', // Required
      'context keys' => array('key 1', 'key2', 'key3', '...'), // Required
      'callback' => NULL,
      'access callback' => NULL,
      'file' => NULL,
    ),
  );
}

/**
 * Alter the content of the serendipity context before serendipity content is gathered.
 */
function hook_serendipity_context_alter(&$context) {
  // Alter the context
}

/**
 * Alter the content of the serendipity results after processing has finished.
 */
function hook_serendipity_results_alter(&$context) {
  // Alter the content
}