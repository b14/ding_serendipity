<?php
/**
 * @file
 * This file contains the api functions which developers can use to
 * influence the serendipity results.
 */

/**
 * Hook to define a serendipity "action"
 * 
 * @return array
 *   An array of serendipity definitions, each of which describe a serendipity
 *   function with the name: module_name . '_' . machine_name . '_serendipity_add'
 *   The definition is required to have the following values:
 *   - "title": The title of the serendipity function
 *   - "description": A description of what the serendipity function provides and when it is applied.
 *   - "context keys": An array of context keys which define the context required before the function
 *     is called by the serendipity module.
 *   The definition can also include the following values:
 *   - "callback": This difines an alternative callback function which replaces the default:
 *     "module_name . '_' . machine_name . '_serendipity_add'".
 *   - "access callback": This defines an alternate access callback function which replaces the default:
 *     "ding_serendipity_access". The access function determines when the serendipity function is applied.
 *   - "file": Path to a file where the serendipity function is written.
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

/**
 * Add results to the serendipity result to prevent empty lists.
 */
function hook_serendipity_fallback($context) {
  // Add fallback content based on the context
}

