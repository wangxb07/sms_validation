<?php

/**
 * @file SMS validation rules
 */

/**
 * SMS validation rules condition
 */
function sms_validation_rules_condition_info() {
  $conditions = array();

  $conditions['sms_validation_current_user_is_actived'] = array(
    'label' => t('SMS validation is passed'),
    'group' => t('SMS Validation'),
    'callbacks' => array(
      'execute' => 'sms_validation_rules_current_user_is_actived',
    ),
  );

  return $conditions;
}

/**
 * callback of rules condition: sms_validaton_current_user_is_actived
 */
function sms_validation_rules_current_user_is_actived() {
  global $user;
  return sms_validation_is_active($user->uid);
}
