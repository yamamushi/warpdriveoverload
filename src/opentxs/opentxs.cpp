/************************************************************
 *
 *  opentxs.cpp
 *
 */

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA1

 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net
 *
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT (PGP Key in license file):
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- otlib.........A class library.......LICENSE:...LAGPLv3
 *   -- otapi.........A client API..........LICENSE:...LAGPLv3
 *   -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
 *   -- otserver......Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (bitcointrader4@gmail.com).
 *  The open-source community has since actively contributed.
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT API, then you
 *   don't have to open-source your code--only your changes to
 *   Open-Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open-Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open-Transactions terms remain respected, with regard to
 *   the Open-Transactions code itself.
 *
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   See Lucre on Github:  https://github.com/benlaurie/lucre
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.

 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.9 (Darwin)

 iQIcBAEBAgAGBQJRSsfJAAoJEAMIAO35UbuOQT8P/RJbka8etf7wbxdHQNAY+2cC
 vDf8J3X8VI+pwMqv6wgTVy17venMZJa4I4ikXD/MRyWV1XbTG0mBXk/7AZk7Rexk
 KTvL/U1kWiez6+8XXLye+k2JNM6v7eej8xMrqEcO0ZArh/DsLoIn1y8p8qjBI7+m
 aE7lhstDiD0z8mwRRLKFLN2IH5rAFaZZUvj5ERJaoYUKdn4c+RcQVei2YOl4T0FU
 LWND3YLoH8naqJXkaOKEN4UfJINCwxhe5Ke9wyfLWLUO7NamRkWD2T7CJ0xocnD1
 sjAzlVGNgaFDRflfIF4QhBx1Ddl6wwhJfw+d08bjqblSq8aXDkmFA7HeunSFKkdn
 oIEOEgyj+veuOMRJC5pnBJ9vV+7qRdDKQWaCKotynt4sWJDGQ9kWGWm74SsNaduN
 TPMyr9kNmGsfR69Q2Zq/FLcLX/j8ESxU+HYUB4vaARw2xEOu2xwDDv6jt0j3Vqsg
 x7rWv4S/Eh18FDNDkVRChiNoOIilLYLL6c38uMf1pnItBuxP3uhgY6COm59kVaRh
 nyGTYCDYD2TK+fI9o89F1297uDCwEJ62U0Q7iTDp5QuXCoxkPfv8/kX6lS6T3y9G
 M9mqIoLbIQ1EDntFv7/t6fUTS2+46uCrdZWbQ5RjYXdrzjij02nDmJAm2BngnZvd
 kamH0Y/n11lCvo1oQxM+
 =uSzz
 -----END PGP SIGNATURE-----
 **************************************************************/

#include "opentxs/core/stdafx.hpp"

#include "opentxs.hpp"

#include "opentxs/client/OTAPI.hpp"
#include "opentxs/client/OpenTransactions.hpp"
#include "opentxs/client/OTClient.hpp"
#include "opentxs/client/OTWallet.hpp"
#include "opentxs/client/ot_commands_ot.hpp"
#include "opentxs/client/ot_otapi_ot.hpp"

#include "opentxs/core/OTAccount.hpp"
#include "opentxs/core/OTAssetContract.hpp"
#include "opentxs/core/OTLog.hpp"
#include "opentxs/core/OTPaths.hpp"
#include "opentxs/core/OTPseudonym.hpp"
#include "opentxs/core/OTServerContract.hpp"
#include "opentxs/core/Version.hpp"


#include <algorithm>
#include <cctype>
#include <functional>


// Stuff for grabbing the home directory
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "util/anyoption.hpp"

using namespace opentxs;
using namespace std;

Opentxs* Opentxs::m_pInstance = NULL;

Opentxs* Opentxs::Instance(){
    if(!m_pInstance)
        m_pInstance = new Opentxs;

    return m_pInstance;
}


const char* categoryName[] = {
    "Category Error",           "Advanced utilities",    "The user wallet",
    "Misc",                     "Markets (bid/ask)",     "Asset accounts",
    "Dealing with other users", "Financial instruments", "Basket currencies",
    "Pseudonyms"};

Opentxs::CommandEntry commands[] = {
    {"acceptall", OT_Command::mainAcceptAll, Opentxs::catAccounts,
     "accept all incoming transfers, receipts, payments, invoices."},
    {"acceptinbox", OT_Command::mainAcceptInbox, Opentxs::catAccounts,
     "accept all incoming transfers and receipts in MyAcct's inbox."},
    {"acceptinvoices", OT_Command::mainAcceptInvoices, Opentxs::catAccounts,
     "pay all invoices in MyNym's payments inbox."},
    {"acceptmoney", OT_Command::mainAcceptMoney, Opentxs::catAccounts,
     "accept all incoming transfers and payments into MyAcct."},
    {"acceptpayments", OT_Command::mainAcceptPayments, Opentxs::catAccounts,
     "accept all incoming payments in MyNym's payments inbox."},
    {"acceptreceipts", OT_Command::mainAcceptReceipts, Opentxs::catAccounts,
     "accept all receipts in MyAcct's inbox."},
    {"accepttransfers", OT_Command::mainAcceptTransfers, Opentxs::catAccounts,
     "accept all incoming transfers in MyAcct's inbox."},
    {"addasset", OT_Command::mainAddAsset, Opentxs::catWallet,
     "paste an existing asset contract, import into your wallet."},
    {"addserver", OT_Command::mainAddServer, Opentxs::catWallet,
     "paste an existing server contract, import into your wallet."},
    {"addsignature", OT_Command::mainAddSignature, Opentxs::catAdmin,
     "add a signature to a contract without releasing others."},
    {"cancel", OT_Command::mainCancel, Opentxs::catInstruments,
     "cancel an uncashed outgoing instrument from outpayment box."},
    {"changepw", OT_Command::mainChangePw, Opentxs::catWallet,
     "change the master passphrase for the wallet."},
    {"checknym", OT_Command::mainCheckNym, Opentxs::catOtherUsers,
     "download a nym's public key based on his ID."},
    {"clearexpired", OT_Command::mainClearExpired, Opentxs::catMisc,
     "clear all expired records."},
    {"clearrecords", OT_Command::mainClearRecords, Opentxs::catMisc,
     "clear all archived records and receipts."},
    {"confirm", OT_Command::mainConfirm, Opentxs::catInstruments,
     "confirm your agreement to a smart contract or payment plan."},
    {"decode", OT_Command::mainDecode, Opentxs::catAdmin,
     "OT-base64-decode out of armor."},
    {"decrypt", OT_Command::mainDecrypt, Opentxs::catAdmin,
     "decrypt ciphertext using nym's private key."},
    {"deleteinmail", OT_Command::mainDeleteInmail, Opentxs::catOtherUsers,
     "delete an in-mail item."},
    {"deleteoutmail", OT_Command::mainDeleteOutmail, Opentxs::catOtherUsers,
     "delete an out-mail item."},
    {"deposit", OT_Command::mainDeposit, Opentxs::catAccounts,
     "deposit cash, cheque, voucher, or invoice."},
    {"discard", OT_Command::mainDiscard, Opentxs::catInstruments,
     "discard an uncashed incoming instrument from payments inbox."},
    {"editaccount", OT_Command::mainEditAccount, Opentxs::catWallet,
     "edit an asset account label, as it appears in your wallet."},
    {"editasset", OT_Command::mainEditAsset, Opentxs::catWallet,
     "edit a currency contract label, as it appears in your wallet."},
    {"editnym", OT_Command::mainEditNym, Opentxs::catWallet,
     "edit the nym label, as it appears in your wallet."},
    {"editserver", OT_Command::mainEditServer, Opentxs::catWallet,
     "edit a server contract label, as it appears in your wallet."},
    {"encode", OT_Command::mainEncode, Opentxs::catAdmin,
     "OT-base64-encode into armor."},
    {"encrypt", OT_Command::mainEncrypt, Opentxs::catAdmin,
     "encrypt plaintext to a nym's public key."},
    {"exchangebasket", OT_Command::mainExchangeBasket, Opentxs::catBaskets,
     "exchange in/out of a basket currency."},
    {"exportcash", OT_Command::mainExportCash, Opentxs::catInstruments,
     "export a cash purse."},
    {"exportnym", OT_Command::mainExportNym, Opentxs::catWallet,
     "export an OT Nym as a single importable file."},
    {"getcontract", OT_Command::mainGetContract, Opentxs::catAdmin,
     "download an asset or server contract by its ID."},
    {"getmarkets", OT_Command::mainGetMarkets, Opentxs::catMarkets,
     "download the list of markets."},
    {"getmyoffers", OT_Command::mainGetMyOffers, Opentxs::catMarkets,
     "download mynym's list of market offers."},
    {"getoffers", OT_Command::mainGetOffers, Opentxs::catMarkets,
     "download the list of market offers."},
    {"getreceipt", OT_Command::mainGetReceipt, Opentxs::catAdmin,
     "downloads a box receipt based on transaction ID."},
    {"importcash", OT_Command::mainImportCash, Opentxs::catInstruments,
     "import a cash purse."},
    {"importnym", OT_Command::mainImportNym, Opentxs::catWallet,
     "import an OT Nym that was previously exported."},
    {"inbox", OT_Command::mainInbox, Opentxs::catAccounts,
     "show inbox of a particular account."},
    {"inmail", OT_Command::mainInmail, Opentxs::catOtherUsers,
     "show in-mail for a particular nym."},
    {"inpayments", OT_Command::mainInpayments, Opentxs::catOtherUsers,
     "show contents of incoming payments box."},
    {"issueasset", OT_Command::mainIssueAsset, Opentxs::catAdmin,
     "issue a currency contract onto an OT server."},
    {"killoffer", OT_Command::mainKillOffer, Opentxs::catMarkets,
     "kill an active recurring market offer."},
    {"killplan", OT_Command::mainKillPlan, Opentxs::catInstruments,
     "kill an active recurring payment plan."},
    {"newaccount", OT_Command::mainNewAccount, Opentxs::catAccounts,
     "create a new asset account."},
    {"newasset", OT_Command::mainNewAsset, Opentxs::catAdmin,
     "create a new asset contract."},
    {"newbasket", OT_Command::mainNewBasket, Opentxs::catBaskets,
     "create a new basket currency."},
    {"newcredential", OT_Command::mainNewCredential, Opentxs::catNyms,
     "create a new credential for a specific nym."},
    {"newkey", OT_Command::mainNewKey, Opentxs::catAdmin,
     "create a new symmetric key."},
    {"newnym", OT_Command::mainNewNym, Opentxs::catNyms, "create a new nym."},
    {"newoffer", OT_Command::mainNewOffer, Opentxs::catMarkets,
     "create a new market offer."},
    {"newserver", OT_Command::mainNewServer, Opentxs::catAdmin,
     "create a new server contract."},
    {"outbox", OT_Command::mainOutbox, Opentxs::catAccounts,
     "show outbox of a particular account."},
    {"outmail", OT_Command::mainOutmail, Opentxs::catOtherUsers,
     "show out-mail for a particular nym."},
    {"outpayment", OT_Command::mainOutpayment, Opentxs::catOtherUsers,
     "show contents of outgoing payments box."},
    {"passworddecrypt", OT_Command::mainPasswordDecrypt, Opentxs::catAdmin,
     "password-decrypt a ciphertext using a symmetric key."},
    {"passwordencrypt", OT_Command::mainPasswordEncrypt, Opentxs::catAdmin,
     "password-encrypt a plaintext using a symmetric key."},
    {"paydividend", OT_Command::mainPayDividend, Opentxs::catMarkets,
     "dividend payout, sent to all shareholders (in voucher form.)"},
    {"payinvoice", OT_Command::mainPayInvoice, Opentxs::catOtherUsers,
     "pay an invoice."},
    {"proposeplan", OT_Command::mainProposePlan, Opentxs::catInstruments,
     "as merchant, propose a payment plan to a customer."},
    {"refresh", OT_Command::mainRefresh, Opentxs::catWallet,
     "performs both refreshnym and refreshaccount."},
    {"refreshaccount", OT_Command::mainRefreshAccount, Opentxs::catAccounts,
     "download latest intermediary files for myacct."},
    {"refreshnym", OT_Command::mainRefreshNym, Opentxs::catNyms,
     "download latest intermediary files for mynym."},
    {"registernym", OT_Command::mainRegisterNym, Opentxs::catAdmin,
     "register a nym onto an OT server."},
    {"revokecredential", OT_Command::mainRevokeCredential, Opentxs::catNyms,
     "revoke one of a nym's credentials."},
    {"sendcash", OT_Command::mainSendCash, Opentxs::catOtherUsers,
     "send cash from mypurse to recipient, withdraw if necessary."},
    {"sendcheque", OT_Command::mainSendCheque, Opentxs::catOtherUsers,
     "write a cheque and then send it to the recipient."},
    {"sendinvoice", OT_Command::mainSendInvoice, Opentxs::catOtherUsers,
     "write an invoice and then send it to the recipient."},
    {"sendmessage", OT_Command::mainSendMessage, Opentxs::catOtherUsers,
     "send a message to another nym's in-mail."},
    {"sendvoucher", OT_Command::mainSendVoucher, Opentxs::catOtherUsers,
     "withdraw a voucher and then send it to the recipient."},
    {"showaccount", OT_Command::mainShowAccount, Opentxs::catAccounts,
     "show account stats for a single account."},
    {"showaccounts", OT_Command::mainShowAccounts, Opentxs::catWallet,
     "show the asset accounts in the wallet."},
    {"showactive", OT_Command::mainShowActive, Opentxs::catInstruments,
     "show the active cron item IDs, or the details of one by ID."},
    {"showassets", OT_Command::mainShowAssets, Opentxs::catWallet,
     "show the currency contracts in the wallet."},
    {"showbalance", OT_Command::mainShowBalance, Opentxs::catAccounts,
     "show balance for a specific account."},
    {"showbasket", OT_Command::mainShowBasket, Opentxs::catBaskets,
     "show basket currencies available in the wallet."},
    {"showcredential", OT_Command::mainShowCredential, Opentxs::catNyms,
     "show a specific credential in detail."},
    {"showcredentials", OT_Command::mainShowCredentials, Opentxs::catNyms,
     "show the credentials for a specific nym."},
    {"showexpired", OT_Command::mainShowExpired, Opentxs::catMisc,
     "show contents of expired record box."},
    {"showmarkets", OT_Command::mainShowMarkets, Opentxs::catMarkets,
     "show the list of markets."},
    {"showmint", OT_Command::mainShowMint, Opentxs::catAdmin,
     "show mint file for specific asset ID. Download if necessary."},
    {"showmyoffers", OT_Command::mainShowMyOffers, Opentxs::catMarkets,
     "show mynym's offers on a particular server and market."},
    {"shownym", OT_Command::mainShowNym, Opentxs::catNyms,
     "show the statistics for a specific nym."},
    {"shownyms", OT_Command::mainShowNyms, Opentxs::catWallet,
     "show the nyms in the wallet."},
    {"showoffers", OT_Command::mainShowOffers, Opentxs::catMarkets,
     "show all offers on a particular server and market."},
    {"showpayment", OT_Command::mainShowPayment, Opentxs::catOtherUsers,
     "show the details of an incoming payment in the payments inbox."},
    {"showpurse", OT_Command::mainShowPurse, Opentxs::catWallet,
     "show contents of cash purse."},
    {"showrecords", OT_Command::mainShowRecords, Opentxs::catMisc,
     "show contents of record box."},
    {"showservers", OT_Command::mainShowServers, Opentxs::catWallet,
     "show the server contracts in the wallet."},
    {"showwallet", OT_Command::mainShowWallet, Opentxs::catWallet,
     "show wallet contents."},
    {"signcontract", OT_Command::mainSignContract, Opentxs::catAdmin,
     "sign a contract, releasing all other signatures first."},
    {"transfer", OT_Command::mainTransfer, Opentxs::catAccounts,
     "send a transfer from myacct to hisacct."},
    {"triggerclause", OT_Command::mainTriggerClause, Opentxs::catInstruments,
     "trigger a clause on a running smart contract."},
    {"verifyreceipt", OT_Command::mainVerifyReceipt, Opentxs::catAccounts,
     "verify your intermediary files against last signed receipt."},
    {"verifysignature", OT_Command::mainVerifySignature, Opentxs::catAdmin,
     "verify a signature on a contract."},
    {"withdraw", OT_Command::mainWithdrawCash, Opentxs::catInstruments,
     "withdraw cash. (From acct on server into local purse.)"},
    {"withdrawvoucher", OT_Command::mainWithdrawVoucher,
     Opentxs::catInstruments,
     "withdraw from myacct as a voucher (cashier's cheque.)"},
    {"writecheque", OT_Command::mainWriteCheque, Opentxs::catInstruments,
     "write a cheque and print it out to the screen."},
    {"writeinvoice", OT_Command::mainWriteInvoice, Opentxs::catInstruments,
     "write an invoice and print it out to the screen."},
    {nullptr, nullptr, Opentxs::catError, nullptr}};

Opentxs::Opentxs()
{
    //OTAPI_Wrap::AppInit();
}

Opentxs::~Opentxs()
{
    OTAPI_Wrap::AppCleanup();
}


bool Opentxs::start(std::vector<std::string> arguments){

    if(OTAPI_Wrap::AppInit()) {

        if(OTAPI_Wrap::OTAPI() == nullptr)
            return false;

        // set up a new argc/argv combo
        int newArgc = arguments.size();
        char **newArgv = new char *[newArgc];
        for (int i = 0; i < newArgc; i++) {
            newArgv[i] = const_cast<char *>(arguments[i].c_str());
        }

        OTAPI_Wrap::OTAPI()->LoadWallet();

        OT_ME madeEasy;
        m_opt = _SharedPtr<AnyOption>(new AnyOption());

        // preprocess the command line
        handleCommandLineArguments(newArgc, newArgv, m_opt.get());

        if (m_opt->getArgc() != 0) {
            processCommand(madeEasy, m_opt.get());
            return false;
        }

        echoCommand = m_opt->getFlag("echocommand") || m_opt->getFlag("test");
        echoExpand = m_opt->getFlag("echoexpand") || m_opt->getFlag("test");
        noPrompt = m_opt->getFlag("noprompt") || m_opt->getFlag("test");

        return true;

    }
    else{
        return false;
    }

}


bool Opentxs::stop(){

    OTAPI_Wrap::AppCleanup();
    cleanupPID();

    return true;
}


void Opentxs::cleanupPID(){

    // Begin Warning
    // This is bad but we're doing it as a temporary workaround while we're debugging this application
    // Don't ever let this hit production, and this is being fixed upstream in opentxs soon anyways
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string dir(homedir);
    std::string otpid(dir + "/.ot/client_data/ot.pid");
    std::remove(otpid.c_str());
    // End Warning

}


void Opentxs::handleCommand(std::string command, std::vector<std::string> arguments){

    if(!m_opt)
        return;

    int newArgc = arguments.size();
    char** newArgv = new char* [newArgc];
    for (int i = 0; i < newArgc; i++) {
        newArgv[i] = const_cast<char*>(arguments[i].c_str());
    }

    AnyOption nopt;
    OT_ME madeEasy;

    handleCommandLineArguments(newArgc, newArgv, &nopt);
    processCommand(madeEasy, &nopt);
}



string& Opentxs::ltrim(string& s)
{
    s.erase(s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

string& Opentxs::rtrim(string& s)
{
    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());
    return s;
}

string& Opentxs::trim(string& s)
{
    return ltrim(rtrim(s));
}

void Opentxs::handleCommandLineArguments(int argc, char* argv[], AnyOption *opt)
{

    OTString configPath(OTPaths::AppDataFolder());
    bool configPathFound = configPath.Exists() && 3 < configPath.GetLength();
    OT_ASSERT_MSG(configPathFound,
                  "RegisterAPIWithScript: Must set Config Path first!\n");
    otWarn << "Using configuration path: " << configPath << "\n";

    opt->addUsage("");
    opt->addUsage(" Opentxs CLI Usage:  ");
    opt->addUsage("");

    opt->setCommandFlag("echocommand");
    opt->setCommandFlag("echoexpand");
    opt->setCommandFlag("errorlist");
    opt->setCommandFlag("noprompt");
    opt->setCommandFlag("test");

    opt->setCommandOption("args");
    opt->setCommandOption("myacct");
    opt->setCommandOption("mynym");
    opt->setCommandOption("mypurse");
    opt->setCommandOption("hisacct");
    opt->setCommandOption("hisnym");
    opt->setCommandOption("hispurse");
    opt->setCommandOption("server");

    // for options that will be checked only from the CLI option file
    opt->setFileOption("defaultserver");
    opt->setFileOption("defaultmyacct");
    opt->setFileOption("defaultmynym");
    opt->setFileOption("defaultmypurse");
    opt->setFileOption("defaulthisacct");
    opt->setFileOption("defaulthisnym");
    opt->setFileOption("defaulthispurse");

    OTString optionsFile("command-line-ot.opt"), iniFileExact;
    bool buildFullPathSuccess =
        OTPaths::RelativeToCanonical(iniFileExact, configPath, optionsFile);
    OT_ASSERT_MSG(buildFullPathSuccess, "Unable to set Full Path");

    opt->processFile(iniFileExact.Get());
    opt->processCommandArgs(argc, argv);

}

const char* Opentxs::getOption(AnyOption *opt, const char* optionName,
                               const char* defaultName)
{
    // can we get the default value from the command line?

    const char* value = opt->getValue(optionName);
    if (value != nullptr) {
        otWarn << "Option  " << optionName << ": " << value << "\n";
        return value;
    }

    // can we get the default value from the options file?
    if (nullptr != defaultName) {
        value = opt->getValue(defaultName);
        if (value != nullptr) {
            otWarn << "Default " << optionName << ": " << value << "\n";
            return value;
        }
    }

    // clear option value
    return "";
}

OTVariable* Opentxs::setGlobalVar(OT_ME& madeEasy, const string& name,
                                  const string& value)
{
    if (value.size() == 0) {
        otInfo << "Variable " << name << " isn't set\n";
        return nullptr;
    }

    otWarn << "Variable " << name << " has value: " << value << "\n";

    OTVariable* var = new OTVariable(name, value, OTVariable::Var_Constant);
    OT_ASSERT(var != nullptr);
    madeEasy.AddVariable(name, *var);
    return var;
}

int Opentxs::processCommand(OT_ME& madeEasy, AnyOption *opt)
{
    // process command line values such as account ID, Nym ID, etc.
    // Also available as defaults in a config file in the ~/.ot folder
    argArgs = getOption(opt, "args", "defaultargs");
    argHisAcct = getOption(opt, "hisacct", "defaulthisacct");
    argHisNym = getOption(opt, "hisnym", "defaulthisnym");
    argHisPurse = getOption(opt, "hispurse", "defaulthispurse");
    argMyAcct = getOption(opt, "myacct", "defaultmyacct");
    argMyNym = getOption(opt, "mynym", "defaultmynym");
    argMyPurse = getOption(opt, "mypurse", "defaultmypurse");
    argServer = getOption(opt, "server", "defaultserver");

    OTWallet* wallet = OTAPI_Wrap::OTAPI()->GetWallet();

    OT_ASSERT_MSG(
        wallet != nullptr,
        "The wallet object is still nullptr, somehow. Please load it.\n");

    OTServerContract* serverContract = nullptr;
    if (argServer.size() > 0) {
        serverContract = wallet->GetServerContract(argServer);
        if (serverContract == nullptr) {
            serverContract = wallet->GetServerContractPartialMatch(argServer);
            if (serverContract == nullptr) {
                otOut << "Unknown default server contract for --server "
                      << argServer << "\n";
            }
        }
        if (serverContract != nullptr) {
            OTString tmp;
            serverContract->GetIdentifier(tmp);
            argServer = tmp.Get();
            otOut << "Using as server: " << argServer << "\n";
        }
    }

    OTPseudonym* myNym = nullptr;
    if (argMyNym.size() > 0) {
        myNym = wallet->GetNymByID(argMyNym);
        if (myNym == nullptr) {
            myNym = wallet->GetNymByIDPartialMatch(argMyNym);
            if (myNym == nullptr) {
                otOut << "Unknown default nym for --mynym " << argMyNym << "\n";
            }
        }
        if (myNym != nullptr) {
            OTString tmp;
            myNym->GetIdentifier(tmp);
            argMyNym = tmp.Get();
            otOut << "Using as mynym: " << argMyNym << "\n";
        }
    }

    OTAccount* myAccount = nullptr;
    if (argMyAcct.size() > 0) {
        myAccount = wallet->GetAccount(argMyAcct);
        if (myAccount == nullptr) {
            myAccount = wallet->GetAccountPartialMatch(argMyAcct);
            if (myAccount == nullptr) {
                otOut << "Unknown default account for --myacct " << argMyAcct
                      << "\n";
            }
        }
        if (myAccount != nullptr) {
            OTString tmp;
            myAccount->GetPurportedAccountID().GetString(tmp);
            argMyAcct = tmp.Get();
            otOut << "Using as myacct: " << argMyAcct << "\n";
        }
    }

    OTPseudonym* hisNym = nullptr;
    if (argHisNym.size() > 0) {
        hisNym = wallet->GetNymByID(argHisNym);
        if (hisNym == nullptr) {
            hisNym = wallet->GetNymByIDPartialMatch(argHisNym);
            if (hisNym == nullptr) {
                otOut << "Unknown default nym for --hisnym " << argHisNym
                      << "\n";
            }
        }
        if (hisNym != nullptr) {
            OTString tmp;
            hisNym->GetIdentifier(tmp);
            argHisNym = tmp.Get();
            otOut << "Using as hisnym: " << argHisNym << "\n";
        }
    }

    OTAccount* hisAccount = nullptr;
    if (argHisAcct.size() > 0) {
        hisAccount = wallet->GetAccount(argHisAcct);
        if (hisAccount == nullptr) {
            hisAccount = wallet->GetAccountPartialMatch(argHisAcct);
            if (hisAccount == nullptr) {
                otOut << "Unknown default account for --hisacct " << argHisAcct
                      << "\n";
            }
        }
        if (hisAccount != nullptr) {
            OTString tmp;
            hisAccount->GetPurportedAccountID().GetString(tmp);
            argHisAcct = tmp.Get();
            otOut << "Using as hisacct: " << argHisAcct << "\n";
        }
    }

    OTIdentifier purseAssetTypeID;
    OTAssetContract* myAssetContract = nullptr;
    if (argMyPurse.size() > 0) {
        myAssetContract = wallet->GetAssetContract(argMyPurse);
        if (myAssetContract == nullptr) {
            myAssetContract = wallet->GetAssetContractPartialMatch(argMyPurse);
            if (myAssetContract == nullptr) {
                otOut << "Unknown default purse for --mypurse " << argMyPurse
                      << "\n";
            }
        }
        if (myAssetContract != nullptr) {
            myAssetContract->GetIdentifier(purseAssetTypeID);
            OTString tmp;
            myAssetContract->GetIdentifier(tmp);
            argMyPurse = tmp.Get();
            otOut << "Using as mypurse: " << argMyPurse << "\n";
        }
    }

    OTIdentifier hisPurseAssetTypeID;
    OTAssetContract* hisAssetContract = nullptr;
    if (argHisPurse.size() > 0) {
        hisAssetContract = wallet->GetAssetContract(argHisPurse);
        if (hisAssetContract == nullptr) {
            hisAssetContract =
                wallet->GetAssetContractPartialMatch(argHisPurse);
            if (hisAssetContract == nullptr) {
                otOut << "Unknown default purse for --hispurse " << argHisPurse
                      << "\n";
            }
        }
        if (hisAssetContract != nullptr) {
            hisAssetContract->GetIdentifier(hisPurseAssetTypeID);
            OTString tmp;
            hisAssetContract->GetIdentifier(tmp);
            argHisPurse = tmp.Get();
            otOut << "Using as hispurse: " << argHisPurse << "\n";
        }
    }

    if (serverContract != nullptr && myNym != nullptr) {
        OTAPI_Wrap::OTAPI()->GetClient()->SetFocusToServerAndNym(
            *serverContract, *myNym,
            OTAPI_Wrap::OTAPI()->GetTransportCallback());
    }

    string command = "list";
    if (opt->getArgc() == 1) {
        command = opt->getArgv(0);
    }
    else {
        otOut << "Expecting a single opentxs command:\n\n";
    }


    typedef unique_ptr<OTVariable> GlobalVar;
    GlobalVar varArgs(setGlobalVar(madeEasy, "Args", argArgs));
    GlobalVar varHisAcct(setGlobalVar(madeEasy, "HisAcct", argHisAcct));
    GlobalVar varHisNym(setGlobalVar(madeEasy, "HisNym", argHisNym));
    GlobalVar varHisPurse(setGlobalVar(madeEasy, "HisPurse", argHisPurse));
    GlobalVar varMyAcct(setGlobalVar(madeEasy, "MyAcct", argMyAcct));
    GlobalVar varMyNym(setGlobalVar(madeEasy, "MyNym", argMyNym));
    GlobalVar varMyPurse(setGlobalVar(madeEasy, "MyPurse", argMyPurse));
    GlobalVar varServer(setGlobalVar(madeEasy, "Server", argServer));

    OTAPI_Func::CopyVariables();

    otWarn << "Script output:\n\n";

    int result = opentxsCommand(command);
    return opt->getArgc() == 1 ? result : -2;
    return -2;
}

int Opentxs::opentxsCommand(const string& command)
{
    if ("exit" == command || "quit" == command) {
        return -2;
    }

    if ("version" == command) {
        otOut << "opentxs " << OPENTXS_VERSION_STRING << "\n";
        otOut << "Copyright (C) 2014 Open Transactions Developers\n";
        return 0;
    }

    if ("list" == command) {
        otOut << "\nCommands:\n\n";
        for (int32_t i = 0; commands[i].command != nullptr; i++) {
            CommandEntry& cmd = commands[i];
            otOut << (cmd.command + spaces18).substr(0, 18);
            if (i % 4 == 3) {
                otOut << "\n";
            }
        }
        otOut << "\n";
        return 0;
    }

    if ("help" == command) {
        // create category groups
        string categoryGroup[catLast];
        for (int i = 1; i < catLast; i++) {
            categoryGroup[i] = string("\n ") + categoryName[i] + ":\n";
        }

        // add commands to their category group
        otOut << "\nCommands:\n";
        for (int32_t i = 0; commands[i].command != nullptr; i++) {
            CommandEntry& cmd = commands[i];
            categoryGroup[cmd.category] +=
                (cmd.command + spaces18).substr(0, 18) + cmd.helpText + "\n";
        }

        // print all category groups
        for (int i = 1; i < catLast; i++) {
            otOut << categoryGroup[i];
        }

        return 0;
    }

    // all other commands.
    for (int32_t i = 0; commands[i].command != nullptr; i++) {
        CommandEntry& cmd = commands[i];
        if (cmd.command == command) {
            int32_t returnValue = (*cmd.function)();
            switch (returnValue) {
            case 0: // no action performed, return success
                return 0;
            case 1: // success
                return 0;
            case -1: // failed
                return -1;
            default: // should not happen
                otOut << "\nUndefined error code: \"" << returnValue
                      << "\".\n\n";
                return -1;
            }
            break;
        }
    }

    otOut << "\nUndefined command: \"" << command << "\" -- Try 'list'.\n\n";
    return -1;
}

int Opentxs::run(std::string command)
{

    if (OTAPI_Wrap::OTAPI() == nullptr)
        return -1;

    if(!m_opt)
        return -1;

    OT_ME madeEasy;


    map<string, string> macros;
    vector<int> errorLineNumbers;
    vector<string> errorCommands;


    int lineNumber = 0;

    int processed = 0;
    while (true) {

        lineNumber++;

        // quit/exit the command loop?
        command = trim(command);


        // empty lines and lines starting with a hash character are seen as
        // comments
        if (command.size() == 0 || command[0] == '#') {
            continue;
        }

        string originalCmd = command;

        // lines starting with a dollar sign character denote the definition of
        // a macro of the form: $macroName = macroValue
        // whitespace around the equal sign is optional
        // <macroName> can be any combination of A-Z, a-z, 0-9, or _
        // <macroValue> is anything after the equal sign and whitespace-trimmed
        // note that <macroValue> can be an empty string
        // note that the dollar sign itself is part of the immediately following
        // macro name
        // note that a macro value stays valid for the entire lifetime of the
        // command loop
        // note that macro expansion is done on the command line before
        // processing the line this means that a macro is allowed to contain
        // command line escape characters
        // note that macro expansion is recursive until no expansions are found
        // any more this means that a macro is allowed to contain other macros
        if (command[0] == '$') {
            // determine the macro name
            size_t nameLength = 1;
            while (nameLength < command.length() &&
                   (isalnum(command[nameLength]) || command[nameLength] == '_')) {
                nameLength++;
            }
            string macroName = command.substr(0, nameLength);

            // skip whitespace
            size_t i = nameLength;
            while (i < command.length() && isspace(command[i])) {
                i++;
            }

            if (i == command.length() || command[i] != '=') {
                otOut << "\n\n***ERROR***\n"
                         "Expected macro definition of the form: "
                         "$macroName = macroValue\n"
                         "Command was: " << command;
                continue;
            }

            // remainder of line after trimming whitespace is macro value
            string macroValue = command.substr(i + 1);
            macros[macroName] = trim(macroValue);
            continue;
        }

        // now replace any macro in the command line with its value
        // unknown macro names will cause an error message instead of command
        // execution
        // note that all macro names are 'maximum munch'
        int expansions = 0;
        for (size_t macro = command.find_first_of("$"); macro != string::npos;
             macro = command.find_first_of("$", macro + 1)) {
            // first see if this is an escaped literal
            if (macro > 0 && command[macro - 1] == '\\') {
                continue;
            }

            // gather rest of macro name 'maximum munch'
            size_t macroEnd = macro + 1;
            while (macroEnd < command.length() &&
                   (isalnum(command[macroEnd]) || command[macroEnd] == '_')) {
                macroEnd++;
            }

            // has this macro been defined?
            string macroName = command.substr(macro, macroEnd - macro);
            auto found = macros.find(macroName);
            if (found == macros.end()) {
                otOut << "\n\n***ERROR***\n"
                         "Macro expansion failed.\n"
                         "Unknown macro: " << macroName
                      << "\n"
                         "Command was: " << command;
                expansions = 100;
                break;
            }

            string& macroValue = found->second;

            // limit to 100 expansions to avoid endless recusion loop
            expansions++;
            if (expansions > 100) {
                otOut << "\n\n***ERROR***\n"
                         "Macro expansion failed.\n"
                         "Too many expansions at macro: " << macroName
                      << "\n"
                         "Command was: " << command;
                break;
            }

            // limit to 10000 characters to avoid crazy recursive expansions
            if (command.length() + macroValue.length() > 10000) {
                otOut << "\n\n***ERROR***\n"
                         "Macro expansion failed.\n"
                         "Command length exceeded at macro: " << macroName
                      << "\n"
                         "Macro value is: " << macroValue
                      << "\n"
                         "Command was: " << command;
                expansions = 100;
                break;
            }

            // expand the command line
            command = command.substr(0, macro) + macroValue + command.substr(macroEnd);
        }

        if (echoExpand && command != originalCmd) {
            otOut << command << endl;
        }

        // skip command when anything during macro expansion failed
        if (expansions > 99) {
            continue;
        }

        // '!' indicates that we expect this command to fail
        //     which is very useful for running a test script
        bool expectFailure = command[0] == '!';

        // Parse command string into its separate parts so it can be passed as
        // an argc/argv combo
        // Whitespace separates args as usual.
        // To include whitespace in an arg surround the entire arg with double
        // quotes
        // An unterminated double-quoted arg will auto-terminate at end of line
        // All characters are taken literal except for: double quote, dollar
        // sign, and backslash
        // To take any character literal, precede it with a backslash
        vector<string> args;

        // add original command name
        args.push_back(command);
        // set up buffer that will receive the separate arguments
        char* buf = new char[command.length() + 1];
        char* arg = buf;

        // start at actual command
        size_t i = expectFailure ? 1 : 0;
        while (i < command.length()) {
            // skip any whitespace
            while (i < command.length() && isspace(command[i])) {
                i++;
            }
            if (i == command.length()) {
                // it was trailing whitespace; we're done
                break;
            }

            // remember where we start this new argument in the buffer
            char* start = arg;

            // unquoted argument?
            if (command[i] != '"') {
                // take everything until end of line or next whitespace
                while (i < command.length() && !isspace(command[i])) {
                    // unescaped literal character?
                    if (command[i] != '\\') {
                        // yep, add to buffer and go for next
                        *arg++ = command[i++];
                        continue;
                    }

                    // take next character literal unless it was the end of line
                    // in which case we simply add the backslash as a literal
                    // character
                    *arg++ = i < command.length() ? command[i++] : '\\';
                }

                // end of argument reached, terminate an add to arguments array
                *arg++ = '\0';
                args.push_back(start);

                // look for next argument
                continue;
            }

            // double quoted argument, skip the quote
            i++;

            // take everything until end of line or next double quote
            while (i < command.length() && command[i] != '"') {
                // unescaped literal character?
                if (command[i] != '\\') {
                    // yep, add to buffer and go for next
                    *arg++ = command[i++];
                    continue;
                }

                // take next character literal unless it was the end of line
                // in which case we simply add the backslash as a literal
                // character
                *arg++ = i < command.length() ? command[i++] : '\\';
            }

            // end of argument reached, terminate an add to arguments array
            *arg++ = '\0';
            args.push_back(start);

            // skip terminating double quote or end of line
            i++;
        }

        // set up a new argc/argv combo
        int newArgc = args.size();
        char** newArgv = new char* [newArgc];
        for (int i = 0; i < newArgc; i++) {
            newArgv[i] = const_cast<char*>(args[i].c_str());
        }

        // preprocess the command line
        AnyOption opt;
        handleCommandLineArguments(newArgc, newArgv, &opt);

        cout << "\n";
        if (expectFailure != (0 != processCommand(madeEasy, &opt))) {
            errorLineNumbers.push_back(lineNumber);
            errorCommands.push_back(originalCmd);
            otOut << "\n\n***ERROR***\n"
                  << (expectFailure ? "Expected command to fail.\nSucceeding"
                                    : "Failed") << " command was: " << command;
        }

        delete[] newArgv;
        delete[] buf;

        otOut << "\n\n";
        processed++;
    }

    int failed = errorLineNumbers.size();
    otOut << "\n\n" << processed << " commands were processed.\n" << failed
         << " commands failed.\n" << endl;

    if (m_opt->getFlag("errorList") || m_opt->getFlag("test")) {
        for (size_t i = 0; i < errorLineNumbers.size(); i++) {
            cout << "\nFailed line " << errorLineNumbers[i] << ": "
                 << errorCommands[i] << endl;
        }
    }

    return failed == 0 ? 0 : -1;

    return 0;
}
